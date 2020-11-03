int* init_stack(int n);
void print_stack (int top, int* stack);
// vr: delete_stack ne renvoie rien et n'a pas besoin de top
void delete_stack(int* stack);
void push(int* stack, int* addresse_top, int operande);
int pop(int* stack, int* top);
