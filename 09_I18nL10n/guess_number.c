#include <stdio.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>

 #define _(STRING) gettext(STRING)

int main()
{
    int low_border = 1;
    int high_border = 100;
    int middle = (high_border + low_border) / 2 ;
    char ans[256];

    setlocale (LC_ALL, "");
    bindtextdomain ("guess_number", ".");
    textdomain ("guess_number");

    printf(_("Choose a number from 1 to 100\n")); 

    while(low_border < high_border){
        printf(_("Is your number greater than %d?\n"), middle);
        printf(_("Answer: (y/n)\n"));
        scanf("%s", &ans);

        if(!strcmp(ans, _("y"))){
            low_border = middle + 1;
        }
        else 
            if(!strcmp(ans, _("n")))
                high_border = middle;
            else {
                printf(_("Wrong input. Please, try again\n"));
                continue;
            }

        if(low_border == high_border) {
            printf(_("The number you chose is %d\n"), low_border);
            break;
        }
        middle = (high_border + low_border) / 2;
    }
    return 0;
}
