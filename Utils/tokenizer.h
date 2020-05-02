#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__


#include <deque>
#include <string>
#include "uncopyable.h"

namespace advcpp
{

class Tokenizer : private Uncopyable
{
public:
	struct NoMoreTokens : public std::exception
	{
		virtual const char* what() const throw();
	};
	
public:
	explicit Tokenizer(const std::string& _delimiters);
	~Tokenizer();

	void TokenizeLine(const std::string& _line) throw();
	std::string PopToken() throw (NoMoreTokens);
	const std::string TopToken() const throw (NoMoreTokens); //XXX Need it?
	void ClearAllTokens() throw();

private:
	std::deque<std::string> m_tokens;
	std::string m_delimStr;
};

} //namespace advcpp


#endif /* __TOKENIZER_H__ */
