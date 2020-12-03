AC_PREREQ([2.69])
AC_INIT(package_buf, 1, anna_example@lapkina_example.com)
AM_INIT_AUTOMAKE([foreign])
LT_INIT([disable-static])
AC_CONFIG_SRCDIR([src/buf.h])
AC_CONFIG_HEADERS([config.h])
AC_LANG(C)

PKG_CHECK_MODULES([CHECK],[check])

# Checks for programs.
AC_PROG_CC

AC_CONFIG_FILES([Makefile tests/Makefile src/Makefile])

AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])
AC_OUTPUT

current_date=$(date)
data=$(echo AC_PACKAGE_NAME  "$PACKAGE_VERSION"  "$current_date")

for filename in $(find src/ -type f -name "*.c" -o -name "*.h")
do
 	if [[ -z "$(grep COMMENT $filename)" ]]
	then
		sed -i -e "1 s/^/\x2F\x2A COMMENT: \"$data\" \x2A\x2F\n/;" $filename
	else
		sed -i "1 s/^.*COMMENT:.*/\x2F\x2A COMMENT: \"$data\" \x2A\x2F/;" $filename
	fi
done

echo "/* COMMENT: $data  */"
