#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include "gen_1ax1b.h"
#include "uniform.h"

static void usage(const char* module_name)
{
    assert(module_name != NULL);
    printf("%s [--file_name output_file_name] [--page_number page_number] type\n", module_name);
}

static void testUniform()
{
    Uniform int_uniform(11, 20);

    printf("int uniform [11, 20)\n");
    for (int i = 0; i < 100; i++) {
        printf("%d  ", (int)int_uniform.next());
    }

    printf("\n\n");

    Uniform double_uniform(11, 20);
    printf("double uniform [11, 20)\n");
    for (int i = 0; i < 100; i++) {
        printf("%lf  ", double_uniform.next());
    }

    printf("\n\n");
}

static void test_getopt(int argc, char **argv)
{
    int c;
    int digit_optind = 0;
    const char* output_file_namename = NULL;
    const char* page_number = NULL;

    while (1)
    {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] =
        {
            { "file_name", required_argument, NULL, 'f' },
            { "page_number", required_argument, NULL, 'p' },
            { NULL, 0, NULL, 0 }
        };

        c = getopt_long(argc, argv, "f:p:", long_options, &option_index);
        if (c == -1) break;

        switch (c)
        {
        case 'f':
            file_name = optarg;
            printf("file_name: %s\n", file_name);
            break;

        case 'p':
            page_number = optarg;
            printf("page_number=%s\n", page_number);
            break;

        default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    printf("argc=%d, optind=%d\n", argc, optind);

    if (optind + 1 != argc)
    {
        usage(argv[0]);
    }

    const char* type = argv[optind];
    printf("type: %s\n", type);

    int i_page_number = atoi(page_number);
    gen_1ax1b(i_page_number, file_name);
}

int main (int argc, char **argv)
{
    test_getopt(argc, argv);
    testUniform();

    return 0;
}
