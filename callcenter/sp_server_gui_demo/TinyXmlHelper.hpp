#ifndef __GRAINS_OF_SAND_HELPER_XML_BY_ERPINGWU__
#define __GRAINS_OF_SAND_HELPER_XML_BY_ERPINGWU__

/** \class helper::xml 
	\brief tinyxapth+tinyxml �򵥰�װ
	\author ���ƽ erpingwu@gmail.com
	\version 2.2
	\n\b history
		- 2009.06.26 v2.2 , ����һ������
		- 2008.09.21 v2.1 , ���Ӽ�������
		- 2008.08.18 v2.0 , ֱ��ʹ�� tinyxpath 1.3.1 �����ں��� tinyxml Ϊ 2.5.3 ���ǵ�ǰ���°汾
								   ���ӽڵ��ı����ã�����ֵ���ã��ļ����漰��湦��
								   boost::regex��Ϊʹ��tr1::regex���ٴ�������ֱ��ʹ�ü򵥵�rfind
		- 2006.04.11 v1.2������ tinyXML_2_4_3 ���������õ�UnitTest.xmlת��ΪUTF-8��ʽ�����Ӷ�<![CDATA[]]>�Ĳ��ԡ�
		- 2005.11.02 v1.1������ GetMultiAttrNodeSet ������
		- 2005.09.08 v1.0��ʹ��tinyXML_2_3_4 �� tinyXPath_1_2_3����Ҫ��tinyXPath�������޸ġ� 
	\date 2005.09.08 - 2008.08.25
	\bug 
	\warning
*/


#include <string>
#include <vector>
#include <map>

class TiXmlDocument;
class TiXmlElement;

	namespace helper
	{
		using std::pair;
		using std::string;
		using std::vector;

		typedef std::pair<string, string> Pair;
		typedef std::vector<Pair> PairSet;
		typedef std::vector<PairSet> PairSetSet;
		

		class xml
		{
		public:
			xml();
			~xml();

			/**	װ��xml�ļ�
			*/
			bool LoadFile(const string& filename);

			/**	�����ļ�
			*/
			bool SaveFile();

			/**	����ļ�
			*/
			bool SaveFile(const char* filename);
			bool SaveFile(const string& filename);

			/** �ӻ�����װ��
			*/
			bool LoadBuffer(const string& str);

			/**ѡ��һ����ֵ��
			*/
			Pair GetPair(const string& xpath);
			
			/**�õ�һ��ֵ
			 */
			string GetValue(const string& xpath);
			string GetValue(const char* xpath);

			/**	ѡ�񵥸����
			\param xpath ��ʽ: /root/node
			*/
			Pair GetSingleNode(const string& xpath);
			string GetNodeValue(const string& xpath);
			string GetNodeValue(const char* xpath);

			/**���ýڵ��ı���
			\param xpath ��ʽ: /root/node��
			\param value 
			 */
			bool SetNode(const string& xpath, const string& value);
			bool SetNode(const char* xpath, const char* value);

			/**	ѡ�񵥸�����
			\param xpath ��ʽ��/root/node/@attr
			*/
			Pair GetSingleAttr(const string& xpath);
			string GetAttrValue(const string& xpath);
			string GetAttrValue(const char* xpath);

			/**��������ֵ
			\param xpath ��ʽ: /root/node/@attr
			\param value 
			*/
			bool SetAttr(const string& xpath, const string& value);
			bool SetAttr(const char* xpath, const char* value);

			/** ѡ��һ������µĶ���ӽ���tag��text��\n
			\code
			<node>
				<subNode1>1</subNode1>
				<subNode2>2</subNode2>
				<subNode3>3</subNode3>
			</node>
			\endcode
			\param xpath ��ʽ: /root/node

			*/
			PairSet GetTagAndTextOfChilds(const string& xpath);

			/** ��ȡ����¶���ӽ��ָ����һ���������ı�
			*/
			PairSet GetKeyAndTextOfChilds(const string& xpath, const string& attrName="key");

			/** ѡ��һ��������ӽ��ı������Լ��ϣ�[i][0].second�ǽ��i���ı�����
			\code
			<node>
				<subNode attr1='1' attr2='2'></subNode>
				<subNode attr1='1'></subNode>
				<subNode attr1='1'attr2='2' attr2='3'></subNode>
			</node>
			\endcode
			\param xpath ��ʽ�� /root/node
			*/
			PairSetSet GetAttrsOfChilds(const string& xpath);
			

			/// ���и��ڵ���ı���Ϊһ���ڵ���� xpath ָ���Ľ��֮��
			bool InsertNode(const string& xpath, const string& text);

			/** �Ƴ� xpath ָ����һ���ڵ� 
			*/
			bool RemoveNode(const string& xpath);

			/** �Ƴ� xpath ָ����ȫ���ڵ� 
			*/
			bool RemoveNodes(const string& xpath);

			/** ����һ���ڵ��µ����нڵ�
			*/
			bool ClearNode(const string& xpath);

			/** �ڵ����Ƿ����ӽڵ�	
			*/
			bool IsEmpty(const string& xpath);

		private:
			TiXmlDocument * xmlDoc_;
			TiXmlElement* xmlRoot_;
			string filename_;

			static const std::string::size_type npos = -1;

		private:
			xml(const xml&);
			xml operator=(const xml&);
		};
	} // namespace helper

#endif

