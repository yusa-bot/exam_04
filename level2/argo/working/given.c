#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> // change this to <stdlib.h>




// streamの1文字を返す
int	peek(FILE *stream)
{
	int	c = getc(stream);
	ungetc(c, stream);
	return c;
}

void	unexpected(FILE *stream)
{
	if (peek(stream) != EOF)
		printf("unexpected token '%c'\n", peek(stream));
	else
		printf("unexpected end of input\n");
}

// streamの1文字とc
int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		(void)getc(stream);
		return 1;
	}
	return 0;
}

int	expect(FILE *stream, char c)
{
	// 有効な文字
	if (accept(stream, c))
		return 1;

	// 有効ではない文字
	unexpected(stream);

	return 0;
}

int	argo(json *dst, FILE *stream)
{
	if (expect(stream, c))
	{


	}
	else

	if (expect(stream, c))
	{
		
	}


}


int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	char *filename = argv[1];
	FILE *stream = fopen(filename, "r");

	json	file;

	// &jsonとstreamを渡す
	if (argo (&file, stream) != 1)
	{
		free_json(file);
		return 1;
	}

	// argo()後のjson
	serialize(file);// データを元に戻す

	printf("\n");
}
