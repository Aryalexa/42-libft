#include <stdio.h>
#include <limits.h>
#include "../ft_printf.h"



void test_ft_printf()
{
	//ft_printf("hola\n", "jaja\n", "jeje\n");
	
	// original behavior
	// min_width (pad->)
	printf("3s :%3s:\n", "hola");//:hola:
	printf("4s :%4s:\n", "hola");//:hola:
	printf("5s :%5s:\n", "hola");//: hola:
	// 0 + min_width (diuxX, indefined for other conversions)
	printf("0d :%0d:\n", 3); //:3:
	printf("03d :%03d:\n", 3); //:003:
	printf("04x :%04x:\n", 17); //:0011:
	// - + min_width (pad <-)
	printf("-d :%-d:\n", 2); //:2:
	printf("-3d :%-3d:\n", 2);//:2  :
	printf("-s :%-s:\n", "hola");  //:hola:
	printf("-3s :%-3s:\n", "hola");//:hola:
	printf("-4s :%-4s:\n", "hola");//:hola:
	printf("-5s :%-5s:\n", "hola");//:hola :
	// .precision : nothing -> 1, .-> 0, 
	// the min number of digits to appear for diuxX,
	// the max number of chars to be printed for s. 
	// When 0 is printed with an explicit precision 0, the output is empty.
	printf("d :%d:\n", 0);   //:0:
	printf(".d :%.d:\n", 0);   //::
	printf(".0d :%.0d:\n", 0); //::
	printf(".0d :%.1d:\n", 0); //:0:
	printf(".1d :%.0d:\n", 55);//:55:
	printf(".d :%.d:\n", 55);  //:55:
	printf(".1d :%.1d:\n", 55);//:55:
	printf(".2d :%.2d:\n", 55);//:55:
	printf(".3d :%.3d:\n", 55);//:055:
	printf(".4s :%.4s:\n", "hola!");//:hola:
	printf(".5s :%.5s:\n", "hola!");//:hola!:
	printf(".6s :%.6s:\n", "hola!");//:hola!:
	//printf(".6.3s :%.6.s:\n", "hola!");// el doble punto lo rompe
	// -0 : 0 < -
	printf("-03d :%-03d:\n", 2);	 //:2  : // warning 0 ignored
	printf("--03d :%-03d:\n", 2);	 //:2  : // warning 0 ignored
	printf("-06s :%-06s:\n", "hola");//:hola  : // warning 0 + s, warning 0 ignored
	// 0.prec : 0 < .prec
	printf("0.3d :%0.3d:\n", 2);	 //:002: 
	printf("04.3d :%04.3d:\n", 2);	 //: 002:
	printf("0.3s :%0.3s:\n", "hola");//:hol: // warning 0 + s
	// -.prec : join
	printf("-5.3d :%-05.3d:\n", 2);     //:002  :
	printf("-5.3s :%-05.3s:\n", "hi");  //:hi   :
	// -0.prec : (0) < (- + .prec)
	printf("-0.3d :%-0.3d:\n", 2);	     //:002:  // warning 0 ignored
	printf("-00.3d :%-00.3d:\n", 2);     //:002: // warning 0 ignored
	printf("-05.3d :%-05.3d:\n", 2);     //:002  : // warning 0 ignored
	printf("-0.3s :%-0.3s:\n", "hola");  //:hol: // warning 0 + s, warning 0 ignored
	printf("--0.3s :%--0.3s:\n", "hola");//:hol: // warning 0 + s, warning 0 ignored
	printf("-0.6s :%-0.6s:\n", "hola");  //:hola: // warning 0 + s, warning 0 ignored
	printf("-3.1s :%-3.1s:\n", "hola");  //:h  : // warning 0 + s, warning 0 ignored
	
	// . + width : join
	printf("4.5d :%4.5d:\n", 457); // :00457:
	printf("5.5d :%5.5d:\n", 457); // :00457:
	printf("6.5d :%6.5d:\n", 457); // : 00457:
	printf("4.5s :%4.5s:\n", "holacarl"); // :holac:
	printf("5.5s :%5.5s:\n", "holacarl"); // :holac:
	printf("6.4s :%6.4s:\n", "holacarl"); // :  hola:
	// %%
	printf("hola :43%   %:\n"); // hola :43%:
	printf("hola :43% %:\n");   // hola :43%:
	printf("hola :43%%: \n");     // hola :43%:
	printf("hola :43%-0# +%: \n"); // hola :43%:
	printf("hola :43%: +#mas\n"); // :43\n // warning invalid conversion sp :, se lo traga!
	printf("hola :43%: %i\n", 1); // :43%i // warning invalid conversion sp :, avanza hasta el % e ignora el :!

	////////////////////////// falta combinar estos con los de arriba
	// # alt form: x-> 0x pref, -> 0X pref, cdipsu no effect
	printf("#x :%#x:\n", 0); // :0:
	printf("#x :%#x:\n", 70); // #x :0x46:
	printf("#X :%#X:\n", 70); // #x :0x46:
	printf("#s :%#s:\n", "hi"); // :hi:
	// ' ' (space) : blank before positive number (d,i)
	printf(" d :% d:\n", 23);   // : 23:
	printf("  d :%  i:\n", 23); // : 23:
	printf(" d :% i:\n", -23);  // :-23:
	// + sign always: + for pos, - for neg (d,i). 
	printf("+i :%+i:\n", 23);   // :+23:
	printf("++i :%++i:\n", 23); // :+23:
	printf("+d :%+d:\n", -23);  // :-23:
	// + > ' '
	printf("+ i :%+ i:\n", 23); // :+23: // ' ' is ignored
	printf(" +i :% +i:\n", 23); // :+23: // ' ' is ignored


}

void prueba_str_avanza(char **str)
{
	(*str)++;
	/* test:
	char *s;
	s = (char *)ft_calloc(5,1);
	s[0] = 'h';
	s[1] = 'i';
	printf("%c\n", *s);
	prueba_str_avanza(&s);
	printf("%c\n", *s);
	free(--s);
	*/
}

int main()
{
	// ft_putstr_fd("-empieza\n", 1);
	// ft_printf("hola\n", "jaja\n", "jeje\n");
	// printf("%x %X", 2147483648, -13);
	// print_unsigned_int(2147483648, 1);
	// ft_putstr_fd("-termina\n", 1);
	
	test_ft_printf();

}