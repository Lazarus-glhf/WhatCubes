#pragma once

template<typename T>
class Optional
{
public:
	Optional() : Elem{nullptr} {}
	Optional(const T& t)
	{
		Elem = new T{t};
	}
	~Optional()
	{
		if (Elem)
		{
			delete Elem;
		}
	}

	T* Get()
	{
		return Elem;
	}
	const T* Get() const
	{
		return Elem;
	}

	T GetOrDefault(T Default) const
	{
		if (Elem)
		{
			return *Elem;
		}
		else
		{
			return Default;
		}
	}
private:
	T* Elem;
};
