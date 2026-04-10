


int	parse_int(json *dst, FILE *stream)
{
	int n = 0;

	fscanf(stream, "%d", &n);
	dst->type = INTEGER;
	dst->integer = n;
	return (1);
}

char *get_str(FILE *stream)
{
	char *res = calloc(4096, sizeof(char));
	int i = 0;
	char c = getc(stream);
	printf("a: %c", c);

	while (1)
	{
		c = getc(stream);
		printf("b: %c", c);

		if (c == '"')
			break ;
		if (c == EOF)
		{
			unexpected(stream);
			return NULL;
		}
		if (c == '\\')
		{
			c = getc(stream);
			printf("c: %c", c);
		}
		res[i++] = c;
	}
	return (res);
}

int parse_map(json *dst, FILE *stream)
{
	dst->type = MAP;
	dst->map.size = 0;
	dst->map.data = NULL;
	char c = getc(stream);

	if (peek(stream) == '}')
		return 1;

	while (1)
	{
		c = peek(stream);
		if (c != '"')
		{
			unexpected(stream);
			return -1;
		}
		dst->map.data = realloc(dst->map.data, (dst->map.size + 1) * sizeof(pair));
		pair *current = &dst->map.data[dst->map.size];
		current->key = get_str(stream);
		if (current->key == NULL)
			return -1;
		dst->map.size++;
		if (expect(stream, ':') == 0)
			return -1;
		if (argo(&current->value, stream) == -1)
			return -1;
		c = peek(stream);
		if (c == '}')
		{
			accept(stream ,c);
			break ;
		}
		if (c == ',')
			accept(stream, c);
		else
		{
			unexpected(stream);
			return -1;
		}
	}
	return 1;
}


int parser(json *dst, FILE *stream)
{
	int c = peek(stream);

	if (c == EOF)
	{
		unexpected(stream);
		return -1;
	}

	if (isdigit(c))
		return (parse_int(dst, stream));

	else if (c == '"')
	{
		dst->type = STRING;
		dst->string = get_str(stream);
		if (dst->string == NULL)
			return (-1);
		return (1);
	}

	else if (c == '{')
		return (parse_map(dst, stream));

	else
	{
		unexpected(stream);
		return -1;
	}
	return (1);
}

int argo(json *dst, FILE *stream)
{
	if (parser(dst, stream) == -1)
		return -1;
	return 1;
}






int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	char *filename = argv[1];
	FILE *stream = fopen(filename, "r");
	if (!stream)
		return (1);
	json	file;
	if (argo (&file, stream) != 1)
	{
		free_json(file);
		return 1;
	}

	serialize(file); // データを元に戻す

	printf("\n");
}

