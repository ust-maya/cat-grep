# Text utilities: my_cat, my_grep.

# Build

For build run `make`.

# Cat

### cat History

> Cat is a command-line utility in Unix and Unix-like operating systems that is used to concatenate and display the content of files. It has been a fundamental utility in Unix since its creation and was originally used to concatenate and display files while preserving spacing and formatting information. The name "cat" stands for concatenate.  
> The cat command has evolved over the years and has many additional features beyond its original functionality. For example, it can be used to copy and concatenate files, display non-printable characters, and display file contents in reverse order. It can also be used to append the contents of one file to another, create new files, and combine multiple files into a single output file.  
> Overall, cat is a powerful and versatile command-line utility that is still widely used in Unix and Unix-like operating systems today. It is a testament to the longevity and flexibility of Unix's design philosophy.

### my_cat Usage

`my_cat [OPTION] [FILE]...`

### my_cat Options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -b | numbers only non-empty lines |
| 2 | -e (implies -v) | but also display end-of-line characters as $  |
| 3 | -n | number all output lines |
| 4 | -s | squeeze multiple adjacent blank lines |
| 5 | -t (implies -v) | but also display tabs as ^I  |
| 6 | -v | display non-printing characters so they are visible.  |

# Grep

### grep History

> Grep is a command-line utility in Unix and Unix-like operating systems that is used to search for specific patterns of characters within a text file. The name "grep" stands for Global Regular Expression Print.  
> The grep command was first developed in the early 1970s as part of the Unix operating system by Ken Thompson and was later improved by Alfred Aho and Peter Weinberger. It was designed to be a simple yet powerful tool for searching through text files and has since become one of the most commonly used utilities in the Unix toolbox.  
> Grep uses regular expressions to match patterns within a text file, allowing users to search for complex patterns of characters. It also supports a range of options and flags that allow users to customize their search and output.  
> Overall, grep is a versatile and powerful tool that has remained a staple of Unix and Unix-like operating systems for over 40 years. It has influenced many other search tools and has become a fundamental component of the Unix philosophy of creating small, modular utilities that can be combined to perform more powerful tasks.

### my_grep Usage

`my_grep [options] template [file_name]`

### my_grep Options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | pattern |
| 2 | -i | Ignore uppercase vs. lowercase.  |
| 3 | -v | Invert match. |
| 4 | -c | Output count of matching lines only. |
| 5 | -l | Output matching files only.  |
| 6 | -n | Precede each matching line with a line number. |
| 7 | -h | Output matching lines without preceding them by file names. |
| 8 | -s | Suppress error messages about nonexistent or unreadable files. |
| 9 | -f file | Take regexes from a file. |
| 10 | -o | Output the matched parts of a matching line. |