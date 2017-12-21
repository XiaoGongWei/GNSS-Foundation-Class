#ifndef GFC_DATATYPEBASE_HPP
#define GFC_DATATYPEBASE_HPP

#include "GException.h"

namespace gfc
{
	
	//���е��������͵Ļ���
	class DataTypeBase
	{
		
	public:
		/// virtual desctuctor
		
		virtual ~DataTypeBase(void) {};
		
		virtual void dump(std::ostream& s) const {}
		
		//���������ʵ�ָú���getClassName()
		virtual GString getClassName(void) const = 0;
				
	private:
		GString m_typeName;   //���������͵�����
				
	};
	
	
}


#endif