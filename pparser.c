//pparser.c

#include <stdio.h>
#include <string.h>

int eval(char **s) {
char c=(*s)[0];
int a, b;

  (*s)++;
  switch(c) {
	case 'f': return 0;
	case 't': return 1;
	case '!': return !eval(s);
	case '|': 
			a = eval(s);
			b = eval(s);
			return a || b;
	case '&': 
			a = eval(s);
			b = eval(s);
			return a && b;
	default:
		printf("EVAL ERROR...\n");
  }
  return -1;
}

int prefix2infixR(char **s) {
char c=(*s)[0];

  (*s)++;
  switch(c) {
	case '\0': return 0;
	case 'f': 
	case 't': 
		printf(" %c ", c);
		return 1;
	case '!':
		printf(" !");
		if(!prefix2infixR(s))
			return 0;
		return 1;
	case '&':
	case '|':
		printf("(");
		if(!prefix2infixR(s))
			return 0;
		printf(" %c ", c);
	        if(!prefix2infixR(s))
			return 0;
		printf(")");
		return 1;
	default:
		return 0;
  }
}

int prefix2infix(char *s) {

  if(!prefix2infixR(&s)){
	printf(" PARSE-ERROR ");
	return 0;
  }

  if(s[0] != '\0') {
	printf(" PARSE-ERROR:  extra junk\n");
	printf("     '%s'\n", s);
	return 0;
  }
  printf("\n");
  return 1;

}
int main(){
int i, n;
char buf[128], *expr;
char ans;

  while(fgets(buf, 127, stdin) != NULL) {
	n = strlen(buf);
	buf[n-1] = '\0';
	printf("prefix: %s\n", buf);
	if(prefix2infix(buf)) {
		expr = buf;
		ans = eval(&expr) ? 't' : 'f';
		printf("   VALUE: %c\n", ans);
	}
	printf("--------\n");
  }
}
