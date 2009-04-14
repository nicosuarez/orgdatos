/* -------------------------------------------------------------------------- */
// Defines.h
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#ifndef _WIKI_ARTICLE_PARSER_DEFINES_
#define _WIKI_ARTICLE_PARSER_DEFINES_

#define PAGE_NODE_DEPTH 1
#define PAGE_NODE_NAME "page"

#define TITLE_NODE_DEPTH 2
#define TITLE_NODE_NAME "title"

#define TEXT_NODE_DEPTH 3
#define TEXT_NODE_NAME "text"

#define LINK_START "[["
#define LINK_END "]]"
#define LINK_TITLE_SEPARATOR '|'
#define LINK_INVALID_SEPARATOR ':'

#define ARTICLE_PARSER_MANAGER_MAX_THREADS 10

#define ARTICLE_PARSER_SAFE_SPLIT_CHAR "\n"
#define ARTICLE_PARSER_LENGTH_X_THREAD 4096

#define DEBUG_ARTICLES_COUNT 100
#define PARSE_RESULT_DUMP_PATH "../dump/parse_result.txt"

#endif

