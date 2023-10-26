#include <stdio.h>
#include <limits.h>
#include "../ft_printf.h"


/*
void test_real_printf()
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
	printf("s :%s:\n", "hola!");//:hola!:
	printf(".0s :%.0s:\n", "hola!");//:: - vacio
	printf(".1s :%.1s:\n", "hola!");//:h:
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
	// -0.prec : (0) < (-w + .prec)
	printf("-0.3d :%-0.3d:\n", 2);	     //:002:  // warning 0 ignored
	printf("-00.3d :%-00.3d:\n", 2);     //:002: // warning 0 ignored
	printf("-05.3d :%-05.3d:\n", 2);     //:002  : // warning 0 ignored
	printf("-0.3s :%-0.3s:\n", "hola");  //:hol: // warning 0 + s, warning 0 ignored
	printf("--0.3s :%--0.3s:\n", "hola");//:hol: // warning 0 + s, warning 0 ignored
	printf("-0.6s :%-0.6s:\n", "hola");  //:hola: // warning 0 + s, warning 0 ignored
	printf("-3.1s :%-3.1s:\n", "hola");  //:h  : // warning 0 + s, warning 0 ignored
	
	// w. : join
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


	//pointer
	int *p;
	a = 2;
	p = &a;
	printf("p :%p:\n", p);      // :0x7ff7b9347760:
	printf("4p :%4p:\n", p);    // :0x7ff7b9347760:
	printf("-4p :%-4p:\n", p);  // :0x7ff7b9347760:
	printf("20p :%20p:\n", p);   //:      0x7ff7b891a760:
	printf("-20p :%-20p:\n", p); //:0x7ff7b891a760      :



}*/

void test_str_pointer_go_forward(char **str)
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

void test_modify_struct(t_conv_specif *cs)
{
	cs->sp = '2'; // al final esto no era asi.....

	// t_conv_specif *cs;
	// printf("created. sp : ");
	// if (!cs->sp)
	// 	printf("NULL\n");
	// else
	// 	printf("%c\n", cs->sp);
	// test_modify_struct(cs);
	// printf("modified. sp : ");
	// if (!cs->sp)
	// 	printf("NULL\n");
	// else
	// 	printf("%c\n", cs->sp);
}

void my_tests_1()
{
	ft_putstr_fd("-empieza\n", 1);

	
	ft_printf("ejemplo 1: hola\n");
	
	int a;
	a = ft_printf("ejemplo 2: h%cla\n", '0');
	ft_putnbr_fd(a, 1);
	ft_putstr_fd("\n", 1);

	a = ft_printf("ejemplo 3: h%sla\n", "34");
	ft_putnbr_fd(a, 1);
	ft_putstr_fd("\n", 1);

	ft_printf("s :%s:\n", "hola!");//:hola!:
	ft_printf(".0s :%.0s:\n", "hola!");//:: - vacio
	ft_printf(".1s :%.1s:\n", "hola!");//:h:
	ft_printf(".4s :%.4s:\n", "hola!");//:hola:
	ft_printf(".5s :%.5s:\n", "hola!");//:hola!:
	ft_printf(".6s :%.6s:\n", "hola!");//:hola!:
	a = ft_printf("-5.3s :%-05.3s:\n", "hi");  //:hi   :
	ft_putnbr_fd(a, 1);
	ft_putstr_fd("\n", 1);

	ft_printf("4.5s :%4.5s:\n", "holacarl"); // :holac:
	ft_printf("5.5s :%5.5s:\n", "holacarl"); // :holac:
	a = ft_printf("6.4s :%6.4s:\n", "holacarl"); // :  hola:
	ft_putnbr_fd(a, 1);
	ft_putstr_fd("\n", 1);

	int *p;
	a = 2;
	p = &a;
	ft_printf("p :%p:\n", p);      // :0x7ff7b9347760:
	ft_printf("4p :%4p:\n", p);    // :0x7ff7b9347760:
	ft_printf("-4p :%-4p:\n", p);  // :0x7ff7b9347760:
	ft_printf("20p :%20p:\n", p);   //:      0x7ff7b891a760:
	ft_printf("-20p :%-20p:\n", p); //:0x7ff7b891a760      :

	ft_putstr_fd("-termina\n", 1); 
}

void my_tests_2()
{
	ft_printf("03d :%03d:\n", 2); // :002:
	ft_printf("03d :%03d:\n", 0); // :000:
	ft_printf("03d :%03d:\n", -2); // :-02:
	ft_printf("00d :%00d:\n", 2); // :2: //0 + w=0 -> nada
	ft_printf("00d :%00d:\n", 0); // :0: //0 + w=0 -> nada
	ft_printf("00d :%00d:\n", -2); // :-2: //0 + w=0 -> nada
	ft_printf(" 03d :% 03d:\n", 4); // : 04:
	ft_printf("+03d :%+03d:\n", 4); // :+04:

	// ft_printf("i :%i:\n", 14);  // :14:
	// ft_printf("i :%i:\n", -14); // :-14:
	// ft_printf("d :%d:\n", 14);  // :14:
	// ft_printf("u :%u:\n", 14);  // :14:
	// ft_printf("u :%u:\n", -14); // :4294967282:
	// ft_printf("x :%x:\n", 14);  // :e:
	// ft_printf("x :%x:\n", -14); // :fffffff2:
	// ft_printf("X :%X:\n", 14);  // :E:
	// ft_printf("pct :%%:\n"); // :%:
	
	ft_printf("d :%d:\n", 0);   //:0:
	ft_printf(".d :%.d:\n", 0);   //::
	ft_printf(".0d :%.0d:\n", 0); //::
	ft_printf("5.0d :%5.0d:\n", 0); //:     :
	ft_printf(".1d :%.1d:\n", 0); //:0:
	ft_printf(".0d :%.0d:\n", 55);//:55:
	ft_printf(".d :%.d:\n", 55);  //:55:
	ft_printf(".1d :%.1d:\n", 55);//:55:
	ft_printf(".2d :%.2d:\n", 55);//:55:
	ft_printf(".3d :%.3d:\n", 55);//:055:
	ft_printf("04d :%04d:\n", -55); //:-055:
	ft_printf(".4d :%.4d:\n", -55); //:-0055:
	ft_printf(".4d :%.4d:\n", 0);   //:0000:
	ft_printf(".4d :%.4d:\n", 55);  //:0055:
	ft_printf("04d :%04d:\n", 55);  //:0055:
	// -0 : 0 < -
	ft_printf("-03d :%-03d:\n", 2);	 //:2  : // warning 0 ignored
	ft_printf("--03d :%-03d:\n", 2);	 //:2  : // warning 0 ignored
	// 0.prec : 0 < .prec
	ft_printf("0.3d :%0.3d:\n", 2);	 //:002: 
	ft_printf("04.3d :%04.3d:\n", 2);	 //: 002:
	// -.prec : join
	ft_printf("-05.3d :%-05.3d:\n", 2);     //:002  :
	ft_printf("-5.3d :%-5.3d:\n", -2);      //:-002 :
	// -0.prec : (0) < (-w + .prec)
	ft_printf("-0.3d :%-0.3d:\n", 2);	     //:002:  // warning 0 ignored
	ft_printf("-00.3d :%-00.3d:\n", 2);     //:002: // warning 0 ignored
	ft_printf("-05.3d :%-05.3d:\n", 2);     //:002  : // warning 0 ignored
	// w. : join
	ft_printf("4.5d :%4.5d:\n", 457); // :00457:
	ft_printf("5.5d :%5.5d:\n", 457); // :00457:
	ft_printf("6.5d :%6.5d:\n", 457); // : 00457:

	// ' ' (space) : blank before positive number (d,i)
	ft_printf(" d :% d:\n", 23);   // : 23:
	ft_printf("  d :%  i:\n", 23); // : 23:
	ft_printf(" d :% i:\n", -23);  // :-23:
	// + sign always: + for pos, - for neg (d,i). 
	ft_printf("+i :%+i:\n", 23);   // :+23:
	ft_printf("++i :%++i:\n", 23); // :+23:
	ft_printf("+d :%+d:\n", -23);  // :-23:
	// + > ' '
	ft_printf("+ i :%+ i:\n", 23); // :+23: // ' ' is ignored
	ft_printf(" +i :% +i:\n", 23); // :+23: // ' ' is ignored
	
	// prec diuxX
	// prec=0, num=0
	ft_printf(".0i :%.0i:\n", 0); //::
	ft_printf("5.0i :%5.0i:\n", 0); //:     :
	ft_printf("5.0u :%5.0u:\n", 0); //:     :
	ft_printf("5.0x :%5.0x:\n", 0); //:     :
	ft_printf("5.0X :%5.0X:\n", 0); //:     :
}

void watch_leaks()
{
	system("leaks a.out");
}


int main()
{
	//atexit(watch_leaks);
	//test_real_printf();
	my_tests_2();
	

}