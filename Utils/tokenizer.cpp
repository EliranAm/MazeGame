#include "tokenizer.h"



namespace advcpp
{

Tokenizer::Tokenizer(const std::string& _delimiters) : m_delimStr(_delimiters)
{
}

Tokenizer::~Tokenizer()
{
}

void Tokenizer::TokenizeLine(const std::string& _line) throw()
{
	size_t tokBegin = 0, tokEnd = 0;

	tokEnd = _line.find_first_of(m_delimStr);
	while(tokEnd != std::string::npos)
	{
		if(tokBegin < tokEnd)
		{
			m_tokens.push_back( _line.substr(tokBegin, tokEnd - tokBegin) );
		}

		tokBegin = tokEnd + 1;
		tokEnd = _line.find_first_of(m_delimStr, tokBegin);
	}

	if(_line.size() > tokBegin)
	{
		m_tokens.push_back( _line.substr(tokBegin,_line.size() - tokBegin) );
	}
}

std::string Tokenizer::PopToken() throw (NoMoreTokens)
{
	if (m_tokens.empty())
	{
		throw NoMoreTokens();
	}

	std::string returnToken(m_tokens.front());
	m_tokens.erase(m_tokens.begin());
	return returnToken;
}

const std::string Tokenizer::TopToken() const throw (NoMoreTokens)
{
	if (m_tokens.empty())
	{
		throw NoMoreTokens();
	}

	return m_tokens.front();
}

void Tokenizer::ClearAllTokens() throw()
{
	m_tokens.clear();
}

const char* Tokenizer::NoMoreTokens::what() const throw()
{
	return "Please, tokenize another line.";
}

} //namespace advcpp




/**TRASH**/
/*
if(' ' != _line[tokEnd] && '\t' != _line[tokEnd])
{
	m_tokens.push_back(_line.substr(tokEnd, 1));
}
*/

