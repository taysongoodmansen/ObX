#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "head.h"

const char* operators[] = {"+","-","/","*","**","\\","%","==","!=",">","<",">=","<=","and","or","xor","contains","starts","->","!>","?"};

double StoD(const char *str, char type) {
	if (type == 'f') {
		return atof(str);
	} else {
		return (double)atoi(str);
	}
}
bool is_operator(const char *token)
{
	int count = sizeof(operators) / sizeof(operators[0]);

	for (int i = 0; i < count; i++)
	{
		if (strcmp(token, operators[i]) == 0)
			return true;
	}

	return false;
}
char short_type(const char* val)
{
	char* type = detect_type(val);

	if (strcmp(type, "integer") == 0) return 'i';
	if (strcmp(type, "float") == 0) return 'f';
	if (strcmp(type, "string") == 0) return 's';
	if (strcmp(type, "bool") == 0) return 'b';
	if (strcmp(type, "resolved path") == 0) return 'p';
	if (strcmp(type, "collection") == 0) return 'c';
	if (strcmp(type, "object") == 0) return 'o';

	return 'u'; // Unknown
}
bool qtc(const char* val, const char* types)
{
	char type = short_type(val);
	bool exclude = types[0] == '-';

	for (int i = exclude ? 1 : 0; types[i] != '\0'; i++)
	{
		char let = types[i];

		if (let == 'a' ||
		        (let == 'n' && (type == 'i' || type == 'f')) ||
		        let == type)
		{
			return !exclude;
		}
	}
	return exclude;
}

ObXValue run_operation(
    char a[128][128], int a_count,
    const char *o,
    char b[128][128], int b_count
)
{
	ObXValue nt = {0};
	strcpy(nt.type, "Null");
	strcpy(nt.value, "Null");

	ObXValue output = {0};
	strcpy(output.type, "Null");
	strcpy(output.value, "Null");

	char atype = (a_count > 1 && strcmp(a[0], "[") == 0)
	             ? 'c' : short_type(a[0]);

	char btype = (b_count > 1 && strcmp(b[0], "[") == 0)
	             ? 'c' : short_type(b[0]);

	printf("%c:%s %c:%s\n", atype, a[0], btype, b[0]);

	bool n_rf = (atype == 'f' || btype == 'f');
	bool r_b = false;

	if (
	    strcmp(o, "+") == 0 ||
	    strcmp(o, "-") == 0 ||
	    strcmp(o, "/") == 0 ||
	    strcmp(o, "*") == 0 ||
	    strcmp(o, "**") == 0 ||
	    strcmp(o, "\\") == 0 ||
	    strcmp(o, "%") == 0 ||
	    strcmp(o, ">") == 0 ||
	    strcmp(o, "<") == 0 ||
	    strcmp(o, ">=") == 0 ||
	    strcmp(o, "<=") == 0
	)
	{
		if (strcmp(o, "*") == 0 && atype == 's')
		{
			if (btype != 'i')
			{
				return_error("Type error: cant repeat by a type of %c", btype);
				return nt;
			}
			char left[128];
			snprintf(left, sizeof(left), "%s", a[0]);

			if (left[0] == '"' && strlen(left) >= 2)
			{
				memmove(left, left + 1, strlen(left));
				left[strlen(left) - 1] = '\0';
			}

			int count = atoi(b[0]);
			output.value[0] = '\0';

			if (count < 0)
			{
				return_error("String repetition count cannot be negative");
			}
			else
			{
				for (int i = 0; i < count; i++)
				{
					if (strlen(output.value) + strlen(left) >= sizeof(output.value))
					{
						return_error("Repeated string exceeds maximum length");
						break;
					}

					strcat(output.value, left);
				}

				char temp[128];
				snprintf(temp, sizeof(temp), "\"%s\"", output.value);
				snprintf(output.value, sizeof(output.value), "%s", temp);

				snprintf(output.type, sizeof(output.type), "string");
			}
			printf("(*) Repeating string by int\n");
			return output;
		}

		if (strcmp(o, "+") == 0 && atype == 's')
		{
			if (btype != 's')
			{
				return_error("Type error: cant join type %c and s", btype);
				return nt;
			}

			printf("(+) Joining two strings\n");
			char left[128];
			char right[128];

			snprintf(left, sizeof(left), "%s", a[0]);
			snprintf(right, sizeof(right), "%s", b[0]);

			left[strlen(left) - 1] = '\0';

			memmove(right, right + 1, strlen(right));

			snprintf(output.type, sizeof(output.type), "string");
			snprintf(output.value, sizeof(output.value), "%s%s", left, right);
			return output;
		}

		if (strcmp(o, "+") == 0 && atype == 'c')
		{
			if (btype == 'c')
				printf("(+) Joining two collections\n");
			else
				printf("(+) Appending list\n");

			return nt;
		}

		if (!qtc(a[0], "n") || !qtc(b[0], "n"))
		{
			if (strcmp(o, "+") == 0)
				return_error("Type error: cant use type %c with + operator", atype);
			else
				return_error("Type error: operator '%s' cannot use types %c and %c",
				             o, atype, btype);

			return nt;
		}

		double a_val = StoD(a[0], atype);
		double b_val = StoD(b[0], btype);
		double rval = 0;

		if (strcmp(o, "+") == 0)
		{
			rval = a_val + b_val;
			printf("(+) Adding two numbers\n");
		}
		else if (strcmp(o, "-") == 0)
		{
			rval = a_val - b_val;
			printf("(-) Subtracting two numbers\n");
		}
		else if (strcmp(o, "/") == 0)
		{
			if (b_val == 0)
			{
				return_error("Cannot divide by zero");
				return nt;
			}

			rval = a_val / b_val;
			n_rf = (rval != (int)rval);
			printf("(/) Dividing two numbers\n");
		}
		else if (strcmp(o, "*") == 0)
		{
			rval = a_val * b_val;
			printf("(*) Multiplying two numbers\n");
		}
		else if (strcmp(o, "**") == 0)
		{
			rval = pow(a_val, b_val);
			printf("(**) Exponentiating two numbers\n");
		}
		else if (strcmp(o, "\\") == 0)
		{
			if (b_val == 0)
			{
				return_error("Cannot integer-divide by zero");
				return nt;
			}

			rval = (double)((long long)a_val / (long long)b_val);
			n_rf = false;
			printf("(\\) Int Diviiding two numbers\n");
		}
		else if (strcmp(o, "%") == 0)
		{
			if (b_val == 0)
			{
				return_error("Cannot modulo by zero");
				return nt;
			}

			rval = fmod(a_val, b_val);
			printf("(%%) Modulating two numbers\n");
		}
		else if (strcmp(o, ">") == 0)
		{
			rval = a_val > b_val;
			r_b = true;
			printf("(>) Greater than with two numbers\n");
		}
		else if (strcmp(o, "<") == 0)
		{
			rval = a_val < b_val;
			r_b = true;
			printf("(<) Less than with two numbers\n");
		}
		else if (strcmp(o, ">=") == 0)
		{
			rval = a_val >= b_val;
			r_b = true;
			printf("(>=) Greater than or equal with two numbers\n");
		}
		else if (strcmp(o, "<=") == 0)
		{
			rval = a_val <= b_val;
			r_b = true;
			printf("(<=) Less than or equal with two numbers\n");
		}

		if (r_b)
		{
			strcpy(output.type, "bool");
			strcpy(output.value, rval != 0 ? "True" : "False");
		}
		else
		{
			strcpy(output.type, n_rf ? "float" : "integer");
			snprintf(output.value, sizeof(output.value), "%g", rval);

			if (n_rf && strchr(output.value, '.') == NULL)
			{
				strncat(
				    output.value,
				    ".0",
				    sizeof(output.value) - strlen(output.value) - 1
				);
			}
		}

		return output;
	}

	else if (strcmp(o, "==") == 0 || strcmp(o, "!=") == 0)
	{
		bool result = false;

		printf("(%s) Comparing two things\n", o);

		if (qtc(a[0], "n") && qtc(b[0], "n"))
		{
			result = StoD(a[0], atype) == StoD(b[0], btype);
		}
		else if (atype != btype)
		{
			result = false;
		}
		else if (atype == 'c')
		{
			// TODO: Compare collection sizes and elements.
			result = false;
		}
		else
		{
			result = strcmp(a[0], b[0]) == 0;
		}

		if (strcmp(o, "!=") == 0)
			result = !result;

		strcpy(output.type, "bool");
		strcpy(output.value, result ? "True" : "False");
		return output;
	}

	else if (
	    strcmp(o, "and") == 0 ||
	    strcmp(o, "or") == 0 ||
	    strcmp(o, "xor") == 0
	)
	{
		if (atype != 'b' || btype != 'b')
		{
			return_error("Type error: cant use %s on type %c and %c",
			             o, btype, atype);
			return nt;
		}
		bool av = strcmp(a[0],"True")==0;
		bool bv = strcmp(b[0],"True")==0;
		bool val;
		if (strcmp(o, "and") == 0) {
			val = av && bv;
		}
		else if (strcmp(o, "or") == 0) {
			val = av || bv;
		}
		else {
			val = av != bv;
		}
		strcpy(output.type, "bool");
		strcpy(output.value, val == true ? "True" : "False");

		printf("(%s) %s with two bools\n", o, o);
		return output;
	}

	else if (strcmp(o, "contains") == 0)
	{
		bool res = false;
		if (atype == 's')
		{
			if (btype != 's')
			{
				return_error("Type error: cant use contains with type %c and s", btype);
				return nt;
			}
			char left[128];
			char right[128];

			snprintf(left, sizeof(left), "%s", a[0]);
			snprintf(right, sizeof(right), "%s", b[0]);

			if (left[0] == '"')
			{
				memmove(left, left + 1, strlen(left));
				left[strlen(left) - 1] = '\0';
			}

			if (right[0] == '"')
			{
				memmove(right, right + 1, strlen(right));
				right[strlen(right) - 1] = '\0';
			}

			res = strstr(left, right) != NULL;
			printf("(contains) contains with two strings\n");
		}
		else if (atype == 'c')
		{
			int idx = 0;
			while (idx < 128&&(strcmp(a[idx],"]"))) {
				if (strcmp(a[idx],b[0])==0) {
					res = true;
					break;
				}
				idx++;
			}
			printf("(contains) contains with a collection and a thing\n");
		}
		else
		{
			return_error("Type error: cant use type %c with contains operator", atype);
			return nt;
		}
		strcpy(output.type, "bool");
		strcpy(output.value, res == true ? "True" : "False");
		return output;
	}

	else if (strcmp(o, "starts") == 0)
	{
		if (atype != 's' || btype != 's')
		{
			return_error("Type error: cant use starts on type %c and %c", btype, atype);
			return nt;
		}

		printf("(starts) starts with two strings\n");
	}

	else if (strcmp(o, "->") == 0)
	{
		// event
	}
	else if (strcmp(o, "!>") == 0)
	{
		// event
	}

	else if (strcmp(o, "?") == 0)
	{
		if (btype != 'b')
		{
			return_error("Type error: cant use filter with type %c", btype);
			return nt;
		}

		printf("(?) filter with thing and bool\n");
		if (strcmp(b[0],"True")==0){
		    snprintf(output.value, sizeof(output.value), "%s", a[0]);
            snprintf(output.type, sizeof(output.type), "%s", detect_type(a[0]));
            return output;
		}
		else{
		    return nt;
		}
	}

	else
	{
		return_error("Unknown operation: %s", o);
		return nt;
	}

	return nt;
}