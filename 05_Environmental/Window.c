
#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#include <stdio.h>
#include <string.h>
#include <pcre2.h>
#include <ncurses.h>

#ifndef UTF_ENCODING
#define UTF_ENCODING 0
#endif

#define DX 3
#define ONLELINE 3
#define MAXSTR 80


/*typedef struct RegexRes {
    char body[MAXSTR];
    int status;
} RegexRes;*/

int regexp_find(char *regexp_pattern, char *subj_str, char *res)
{
    pcre2_code *re;
    PCRE2_SPTR pattern;     /* PCRE2_SPTR is a pointer to unsigned code units of */
    PCRE2_SPTR subject;     /* the appropriate width (in this case, 8 bits). */

    int errnum;
    int i, rc;
    //res->status = 0;

    PCRE2_SIZE erroffs;
    PCRE2_SIZE *ovector;
    PCRE2_SIZE subject_length;

    pcre2_match_data *match_data;

    pattern = (PCRE2_SPTR)regexp_pattern;
    subject = (PCRE2_SPTR)subj_str;
    subject_length = (PCRE2_SIZE)strlen((char *)subject);

    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);
    if (UTF_ENCODING == 1) {
        re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);
    } else {
        re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &errnum, &erroffs, NULL);
    }

    if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errnum, buffer, sizeof(buffer));
        printf(res, "PCRE2 compilation failed at offset %d: %s\n", (int)erroffs, buffer);
        return 1;
    }

    match_data = pcre2_match_data_create_from_pattern(re, NULL);

    rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
        switch(rc) {
        case PCRE2_ERROR_NOMATCH:
            printf(res, "No match\n");
            //res->status = 1; 
            break;
        default:
            printf(res, "Matching error %d\n", rc);
           // res->status = 1; 
            break;
        }
        pcre2_match_data_free(match_data);   /* Release memory used for the match */
        pcre2_code_free(re);  
                      /*   data and the compiled pattern. */
        return 1;
    }

    ovector = pcre2_get_ovector_pointer(match_data);

    for (i = 0; i < rc; i++)
        sprintf(res, "%2ld: %.*s\n", ovector[2*i], 
                 (int)(ovector[2*i+1] - ovector[2*i]),
                 subject + ovector[2*i]);

    pcre2_match_data_free(match_data);  /* Release the memory that was used */
    pcre2_code_free(re);                /* for the match data and the pattern. */

    return 0;
}


void main() {
    WINDOW *winA, *winB, *winO;
    char inA[MAXSTR], inB[MAXSTR];
    int c = 0;
    int half;
    //RegexpRes res;
    //res.status = 0;
    //res.body = (char *)calloc(MAXSTR, sizeof(char));
    char res[MAXSTR];

    initscr();
    cbreak();
    printw("Input:");
    refresh();

    half = (COLS-2*DX)/2;
    winA = newwin(ONLELINE, half, DX, DX);
    winB = newwin(ONLELINE, half, DX, DX+half);
    winO = newwin(LINES-ONLELINE-DX*2, (COLS-2*DX), DX+ONLELINE, DX);
    keypad(winA, TRUE);
    keypad(winB, TRUE);
    scrollok (winO, TRUE);
    wmove(winO, 1, 0);
    do {
        werase(winA); 
        box(winA, 0, 0);
        mvwgetnstr(winA, 1, 1, inA, MAXSTR);
        werase(winB); 
        box(winB, 0, 0);
        mvwgetnstr(winB, 1, 1, inB, MAXSTR);
        wprintw(winO, "%s: %s \n", inA, inB);
        regexp_find(inA, inB, res);
        wprintw(winO, "%s\n", res);
        box(winO, 0, 0);
        wrefresh(winO);
    } while(*inA);

    endwin();
  //  free(res.body);

}
