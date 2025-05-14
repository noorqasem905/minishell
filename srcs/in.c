/* env.c
execution.c

 */

/* execute redirection */
/*


let say that we have twe type of:
1: command < file command_continues
2: < file command command_continues

lets say that
we have the first
command < file command_continues

excute_varaible: temp
temp: command command_continues
temp2: file(redirection[0])

issue here: 
command < file command_continues < file < file .....
in the first we have to save command in one varaible
in the second we have to change to files


implement:
1: save the first command







command1: ls < in in < in
command2: ls << end > kk





till one case should handle, which is command 2, should include all cases like it ;> good luck...






<- here doc part ->

you have to re handle here doc  
KO -- > << end <<
KO -- > << end <
KO -- > ls << end ls (no switch file named ls)
------------------------------
OK -- > << end < in
OK -- > ls << end  in< in
------------------------------










... continue after pray in mosque (لا اله الا الله محمد رسول الله)
*/