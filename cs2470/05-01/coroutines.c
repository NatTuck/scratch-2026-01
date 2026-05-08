#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

static ucontext_t main_ctx, f1_ctx, f2_ctx;

void
function1(void)
{
    for (int i = 0; i < 3; i++) {
        printf("Function 1, iteration %d\n", i);
        swapcontext(&f1_ctx, &f2_ctx); // Yield to function2
    }
    printf("Function 1 done\n");
    swapcontext(&f1_ctx, &main_ctx); // Return to main
}

void
function2(void)
{
    for (int i = 0; i < 3; i++) {
        printf("Function 2, iteration %d\n", i);
        swapcontext(&f2_ctx, &f1_ctx); // Yield to function1
    }
    printf("Function 2 done\n");
    swapcontext(&f2_ctx, &main_ctx); // Return to main
}

int
main()
{
    // Allocate stacks for the two functions
    char* stack1 = malloc(8192);
    char* stack2 = malloc(8192);

    getcontext(&f1_ctx);
    f1_ctx.uc_stack.ss_sp = stack1;
    f1_ctx.uc_stack.ss_size = 8192;
    f1_ctx.uc_link = &main_ctx; // Where to go when f1 finishes
    makecontext(&f1_ctx, function1, 0);

    getcontext(&f2_ctx);
    f2_ctx.uc_stack.ss_sp = stack2;
    f2_ctx.uc_stack.ss_size = 8192;
    f2_ctx.uc_link = &main_ctx;
    makecontext(&f2_ctx, function2, 0);

    printf("Starting cooperative multitasking...\n");
    swapcontext(&main_ctx, &f1_ctx);

    printf("Back in main!\n");
    free(stack1);
    free(stack2);
    return 0;
}
