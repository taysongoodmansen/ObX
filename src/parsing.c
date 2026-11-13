#include <string.h>
#include <stdio.h>

#include "head.h"

void replace_tokens(
    char tokens[128][128],
    int *token_count,
    int start,
    int end,
    char replacement[128][128],
    int replacement_count
)
{
	int old_length = end - start + 1;
	int difference = replacement_count - old_length;

	if (difference > 0)
	{
		for (int i = *token_count - 1; i > end; i--)
		{
			strcpy(tokens[i + difference], tokens[i]);
		}
	}
	else if (difference < 0)
	{
		for (int i = end + 1; i < *token_count; i++)
		{
			strcpy(tokens[i + difference], tokens[i]);
		}
	}

	for (int i = 0; i < replacement_count; i++)
	{
		strcpy(tokens[start + i], replacement[i]);
	}

	*token_count += difference;
}

void resolve_expression(
    char tokens[128][128],
    int *token_count,
    int start,
    int end,
    char result[128][128],
    int *result_count,
    bool replace_path,
    char *scabkey
)
{
	if (start == end && strcmp(tokens[start], "Null") == 0)
	{
		strcpy(result[0], "Null");
		*result_count = 1;
		return;
	}
	*result_count = end - start + 1;

	for (int i = start; i <= end; i++)
	{
		strcpy(result[i - start], tokens[i]);
	}
	if (strcmp(scabkey,"")!=0) {
		if (strcmp(scabkey,"ref")==0) {
			replace_path = false;
		}
	}
	for (int i = start; i <= end; i++)
	{
		if (!is_operator(tokens[i]))
			continue;

		if (i == start || i == end)
		{
			return_error("Operator '%s' is missing an operand", tokens[i]);
			return;
		}

		char left_tokens[128][128];
		char right_tokens[128][128];

		int left_count = i - start;
		int right_count = end - i;

		for (int j = 0; j < left_count; j++)
			strcpy(left_tokens[j], tokens[start + j]);

		for (int j = 0; j < right_count; j++)
			strcpy(right_tokens[j], tokens[i + 1 + j]);

		char left_result[128][128];
		char right_result[128][128];

		int left_result_count = 0;
		int right_result_count = 0;

		resolve_expression(
		    left_tokens, &left_count,
		    0, left_count - 1,
		    left_result, &left_result_count,
		    replace_path, scabkey
		);

		resolve_expression(
		    right_tokens, &right_count,
		    0, right_count - 1,
		    right_result, &right_result_count,
		    replace_path, scabkey
		);

		ObXValue value = run_operation(left_result, left_result_count,tokens[i],right_result, right_result_count);
		printf("operator output of v:%s and t:%s\n",value.value,value.type);

		strcpy(result[0], value.value);
		*result_count = 1;
		return;
	}
	if (start == end && strncmp(tokens[start], "§", strlen("§")) == 0)
	{
		return;
	}
	if (*result_count == 1) {
		char *type = detect_type(tokens[start]);
		if (strcmp(type,"unknown") == 0) {
			char path[512];

			resolve_path(
			    current_path,
			    result,
			    0,
			    *result_count - 1,
			    path
			);
			if (strcmp(scabkey, "ref") == 0)
			{
				char marked_path[128];

				strcpy(marked_path, "§");
				strcat(marked_path, path);

				strcpy(path, marked_path);
			}
			char val[128];
			strcpy(val,path);
			if (replace_path) {
				int index = find_variable(path);
				strcpy(val,variables[index].value);
			}
			strcpy(result[0], val);
			*result_count = 1;
		}
		else {
		}
	}
	else {
		if (strcmp(tokens[start], "[") == 0)
		{
			char tmpresult[128][128];
			int tmpresultcount = 0;

			char tmphold[128][128];
			int tmpholdcount = 0;

			int bracket_depth = 1;

			for (int i = start + 1; i < end && bracket_depth > 0; i++)
			{
				char *cur = tokens[i];

				if (strcmp(cur, "[") == 0)
				{
					bracket_depth++;
					strcpy(tmphold[tmpholdcount++], cur);
				}
				else if (strcmp(cur, "]") == 0)
				{
					bracket_depth--;

					if (bracket_depth > 0)
						strcpy(tmphold[tmpholdcount++], cur);
				}
				else if (
				    (strcmp(cur, ",") == 0 || strcmp(cur, ":") == 0)
				    && bracket_depth == 1
				)
				{
					if (tmpholdcount == 0)
					{
						return_error("Can't have a collection entry with no value");
						return;
					}

					char colqresult[128][128];
					int colqresult_count = 0;
					int tmphold_token_count = tmpholdcount;

					resolve_expression(
					    tmphold,
					    &tmphold_token_count,
					    0,
					    tmphold_token_count - 1,
					    colqresult,
					    &colqresult_count,
					    true,
					    ""
					);

					if (tmpresultcount + colqresult_count + 1 >= 128)
					{
						return_error("Collection has too many tokens");
						return;
					}

					for (int q = 0; q < colqresult_count; q++)
					{
						strcpy(tmpresult[tmpresultcount++], colqresult[q]);
					}

					strcpy(tmpresult[tmpresultcount++], cur);

					tmpholdcount = 0;
				}
				else
				{
					strcpy(tmphold[tmpholdcount++], cur);
				}
			}

			if (tmpholdcount > 0)
			{
				char colqresult[128][128];
				int colqresult_count = 0;
				int tmphold_token_count = tmpholdcount;

				resolve_expression(
				    tmphold,
				    &tmphold_token_count,
				    0,
				    tmphold_token_count - 1,
				    colqresult,
				    &colqresult_count,
				    true,
				    ""
				);

				if (tmpresultcount + colqresult_count >= 128)
				{
					return_error("Collection has too many tokens");
					return;
				}

				for (int q = 0; q < colqresult_count; q++)
				{
					strcpy(tmpresult[tmpresultcount++], colqresult[q]);
				}
			}

			char replacement[128][128];
			int replacement_count = 0;

			strcpy(replacement[replacement_count++], "[");

			for (int i = 0; i < tmpresultcount; i++)
			{
				strcpy(replacement[replacement_count++], tmpresult[i]);
			}

			strcpy(replacement[replacement_count++], "]");

			memcpy(result, replacement, replacement_count * sizeof(result[0]));
			*result_count = replacement_count;
			return;
		}
		else {
			char path[512];

			resolve_path(
			    current_path,
			    result,
			    0,
			    *result_count - 1,
			    path
			);
			if (strcmp(scabkey, "ref") == 0)
			{
				char marked_path[128];

				strcpy(marked_path, "§");
				strcat(marked_path, path);

				strcpy(path, marked_path);
			}
			char val[128];
			strcpy(val,path);
			if (replace_path) {
				int index = find_variable(path);
				if (index>-1) {
					strcpy(val,variables[index].value);
				}
				else {
					strcpy(val,"Null");
				}
			}
			strcpy(result[0],val);
			*result_count = 1;
		}
	}
}

char *parse(
    char tokens[128][128],
    int *token_count,
    int left_par,
    int right_par
)
{
	char pieces[128][128];
	int length = 0;

	for (int i = left_par + 1; i < right_par; i++)
	{
		strcpy(pieces[length], tokens[i]);
		length++;
	}

	if (in("(", pieces, length))
	{
		process_tokens(pieces, &length);

		right_par = left_par + length + 1;
	}
	char scabkey[128] = "";
	if (strcmp(tokens[left_par-1],"¤")==0) {
		strcpy(scabkey,tokens[left_par-2]);
	}

	char result[128][128];
	int result_count;

	resolve_expression(
	    pieces,
	    token_count,
	    0,
	    length - 1,
	    result,
	    &result_count,
	    true,
	    scabkey
	);

	if (strcmp(scabkey, "") != 0)
	{
		replace_tokens(
		    tokens,
		    token_count,
		    left_par - 2,
		    right_par,
		    result,
		    result_count
		);

		return NULL;
	}

	for (int i = 0; i < result_count; i++)
	{
		strcpy(pieces[i], result[i]);
	}

	length = result_count;

	char *prev_token = tokens[left_par - 1];

	bool keep_par =
	    (varchar(prev_token[strlen(prev_token) - 1]) == 1);

	int old_length = right_par - left_par + 1;
	int new_length = length;

	if (keep_par)
	{
		char replacement[128][128];
		int replacement_count = length + 2;

		strcpy(replacement[0], "func(");

		for (int i = 0; i < length; i++)
		{
			strcpy(replacement[i + 1], pieces[i]);
		}

		strcpy(replacement[length + 1], "func)");

		replace_tokens(
		    tokens,
		    token_count,
		    left_par,
		    right_par,
		    replacement,
		    replacement_count
		);
	}
	else
	{
		int difference = new_length - old_length;

		if (difference != 0)
		{
			for (int i = *token_count - 1; i > right_par; i--)
			{
				strcpy(tokens[i + difference], tokens[i]);
			}
		}

		for (int i = 0; i < new_length; i++)
		{
			strcpy(tokens[left_par + i], pieces[i]);
		}

		*token_count += difference;
	}

	return NULL;
}

