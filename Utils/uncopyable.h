#ifndef __UNCOPYABLE_H__
#define __UNCOPYABLE_H__

namespace advcpp
{

class Uncopyable
{
public:
	Uncopyable(){}
	virtual ~Uncopyable(){}
	
private:
	Uncopyable(const Uncopyable &);
	Uncopyable& operator=(const Uncopyable &);
	
};


} //namespace advcpp

#endif /* __UNCOPYABLE_H__ */

