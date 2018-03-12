#ifndef __FINAL_CLASS__
#define __FINAL_CLASS__

class Final;

class FinalHelper
{
	private:
		FinalHelper() {}
		friend class Final;
};

class Final : virtual public FinalHelper
{
	public:
		Final() = default;

		Final(int data)
			:m_iData(data)
		{}

		int GetData() { return m_iData; }
		void SetData(int data) { m_iData = data; }
	private:
		int m_iData;
};

class Derived : public Final
{
	private:
		int m_iD_Data;
};

#endif