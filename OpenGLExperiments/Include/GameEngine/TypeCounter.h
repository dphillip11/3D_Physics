#pragma once
class TypeIDCounter {
public:
	template<typename T>
	static int GetID() {
		static int id = counter_++;
		return id;
	}
private:
	static int counter_;
};


template<typename T>
class TypeID {
public:
	static int Get() {
		return TypeIDCounter::GetID<T>();
	}
};