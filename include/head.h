#define NMS 128

#ifndef RunAllH
#define RunAllH
int RunFile(FILE *file);
extern char current_path[128];
extern int path_idx;
extern int current_line;
#endif

#ifndef SingleLineH
#define SingleLineH
void process_single_line(char line[1024]);
int varchar(char character);
void tmplist_print(char tokens[128][128], int token_count);
#endif

#ifndef ProcessTokensH
#define ProcessTokensH
void process_tokens(char tokens[128][128],int *token_count);
#include <stdbool.h>
bool in(const char *target, char tokens[128][128], int token_count);
#endif

#ifndef VariablesH
#define VariablesH
void set_variable_value(char path[128],char value[128]);
int is_num(const char value[128]);

typedef struct
{
    char path[512];
    char type[32];

    union
    {
        char value[128];
        struct
        {
            int attribute_count;
            int attributes[128];
        } object;
    };

} ObXValue;

extern ObXValue variables[128];
extern int variable_count;
int find_variable(const char *path);
int create_object(const char *path);
char *detect_type(const char value[128]);
bool remove_last_path_segment(char path[512]);
void assign_collection(const char *parent,char tokens[128][128],const int leftbrac,const int rightbrac);
#endif

#ifndef pathsH
#define pathsH
void resolve_path(const char *current_path,char tokens[128][128],int start,int end,char path[512]);
bool is_resolved_path(const char *value);
void remove_resolved_marker(const char *value, char path[128]);
#endif

#ifndef parsingH
#define parsingH
char *parse(char tokens[128][128],int *token_count,int left_par, int right_par);
void resolve_expression(char tokens[128][128],int *token_count,int start,int end,char result[128][128],int *result_count,bool replace_path,char *scabkey);
void replace_tokens(char tokens[128][128],int *token_count,int start,int end,char replacement[128][128],int replacement_count);
#endif

#ifndef errorsH
#define errorsH
void return_error(const char *format, ...);
#endif

#ifndef operatorsH
#define operatorsH
extern const char *operators[];
ObXValue run_operation(char a[128][128], int a_count,const char *o,char b[128][128], int b_count);
bool is_operator(const char *token);
#endif