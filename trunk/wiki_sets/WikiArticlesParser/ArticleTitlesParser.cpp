/* -------------------------------------------------------------------------- */
// ArticleTitlesParser.cpp
// Developers: Leandro Oscar Mencias
//						 Nicolás Suarez
/* -------------------------------------------------------------------------- */

#include "ArticleTitlesParser.h"

ArticleTitlesParser::ArticleTitlesParser()
{
}

/* -------------------------------------------------------------------------- */

ArticleTitlesParser::~ArticleTitlesParser()
{
}

/* -------------------------------------------------------------------------- */

void ArticleTitlesParser::Parse(const ustring *text, ParseResult *results)
{
	ustring::size_type iEnd = 0;
	ustring::size_type iStart = text->find(LINK_START);

	bool hasInnerLinks = false;
	ustring::size_type innerStart = 0;

	while (iStart != ustring::npos && iEnd != ustring::npos)
	{
		iStart += 2;
		iEnd = text->find(LINK_END, iStart);

		hasInnerLinks = false;
		innerStart = text->find(LINK_START, iStart);

		while (innerStart != ustring::npos && iEnd != ustring::npos && innerStart < iEnd)
		{
			iEnd += 2;
			hasInnerLinks = true;

			iEnd = text->find(LINK_END, iEnd);
			innerStart = text->find(LINK_START, iEnd);
		}

		if (iEnd != ustring::npos)
		{
			ustring link = text->substr(iStart, (iEnd - iStart));

			if (hasInnerLinks)
				this->Parse(&link, results);

			if (this->IsArticleTitleLink(link))
			{
				ustring title = this->GetArticleTitle(link);

				if (!title.empty())
					results->Add(title);
			}

			iEnd += 2;
			iStart = text->find(LINK_START, iEnd);
		}
	}
}

/* -------------------------------------------------------------------------- */

ustring ArticleTitlesParser::GetArticleTitle(const ustring &link) const
{
	ustring::size_type index = link.find(LINK_TITLE_SEPARATOR);
	ustring title = (index == ustring::npos) ? link : link.substr(0, index);

	return title.uppercase();
}

/* -------------------------------------------------------------------------- */

bool ArticleTitlesParser::IsArticleTitleLink(const ustring &link) const
{
	if (link.find(LINK_INVALID_SEPARATOR) != ustring::npos)
		return false;

	return true;
}

