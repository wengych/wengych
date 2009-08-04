#ifndef __GRAINS_OF_SAND_HELPER_XML_BY_ERPINGWU__
#define __GRAINS_OF_SAND_HELPER_XML_BY_ERPINGWU__

/** \class helper::xml 
	\brief tinyxapth+tinyxml 简单包装
	\author 吴尔平 erpingwu@gmail.com
	\version 2.2
	\n\b history
		- 2009.06.26 v2.2 , 增加一个函数
		- 2008.09.21 v2.1 , 增加几个函数
		- 2008.08.18 v2.0 , 直接使用 tinyxpath 1.3.1 ，其内含的 tinyxml 为 2.5.3 ，是当前最新版本
								   增加节点文本设置，属性值设置，文件保存及另存功能
								   boost::regex改为使用tr1::regex，再次抛弃，直接使用简单的rfind
		- 2006.04.11 v1.2，改用 tinyXML_2_4_3 ，将测试用的UnitTest.xml转换为UTF-8格式，增加对<![CDATA[]]>的测试。
		- 2005.11.02 v1.1，增加 GetMultiAttrNodeSet 函数。
		- 2005.09.08 v1.0，使用tinyXML_2_3_4 与 tinyXPath_1_2_3，需要对tinyXPath做少许修改。 
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
		// using std::pair;
		// using std::string;
		// using std::vector;

		typedef std::pair<std::string, std::string> Pair;
		typedef std::vector<Pair> PairSet;
		typedef std::vector<PairSet> PairSetSet;
		

		class xml
		{
		public:
			xml();
			~xml();

			/**	装入xml文件
			*/
			bool LoadFile(const std::string& filename);

			/**	保存文件
			*/
			bool SaveFile();

			/**	另存文件
			*/
			bool SaveFile(const char* filename);
			bool SaveFile(const std::string& filename);

			/** 从缓冲中装入
			*/
			bool LoadBuffer(const std::string& str);

			/**选择一个键值对
			*/
			Pair GetPair(const std::string& xpath);
			
			/**得到一个值
			 */
			std::string GetValue(const std::string& xpath);
			std::string GetValue(const char* xpath);

			/**	选择单个结点
			\param xpath 格式: /root/node
			*/
			Pair GetSingleNode(const std::string& xpath);
			std::string GetNodeValue(const std::string& xpath);
			std::string GetNodeValue(const char* xpath);

			/**设置节点文本、
			\param xpath 格式: /root/node、
			\param value 
			 */
			bool SetNode(const std::string& xpath, const std::string& value);
			bool SetNode(const char* xpath, const char* value);

			/**	选择单个属性
			\param xpath 格式：/root/node/@attr
			*/
			Pair GetSingleAttr(const std::string& xpath);
			std::string GetAttrValue(const std::string& xpath);
			std::string GetAttrValue(const char* xpath);

			/**设置属性值
			\param xpath 格式: /root/node/@attr
			\param value 
			*/
			bool SetAttr(const std::string& xpath, const std::string& value);
			bool SetAttr(const char* xpath, const char* value);

			/** 选择一个结点下的多个子结点的tag与text：\n
			\code
			<node>
				<subNode1>1</subNode1>
				<subNode2>2</subNode2>
				<subNode3>3</subNode3>
			</node>
			\endcode
			\param xpath 格式: /root/node

			*/
			PairSet GetTagAndTextOfChilds(const std::string& xpath);

			/** 读取结点下多个子结点指定的一个属性与文本
			*/
			PairSet GetKeyAndTextOfChilds(const std::string& xpath, const std::string& attrName="key");

			/** 选择一个结点下子结点的本身及属性集合，[i][0].second是结点i的文本内容
			\code
			<node>
				<subNode attr1='1' attr2='2'></subNode>
				<subNode attr1='1'></subNode>
				<subNode attr1='1'attr2='2' attr2='3'></subNode>
			</node>
			\endcode
			\param xpath 格式： /root/node
			*/
			PairSetSet GetAttrsOfChilds(const std::string& xpath);
			

			/// 将有根节点的文本做为一个节点加入 xpath 指定的结点之下
			bool InsertNode(const std::string& xpath, const std::string& text);

			/** 移出 xpath 指定的一个节点 
			*/
			bool RemoveNode(const std::string& xpath);

			/** 移出 xpath 指定的全部节点 
			*/
			bool RemoveNodes(const std::string& xpath);

			/** 清理一个节点下的所有节点
			*/
			bool ClearNode(const std::string& xpath);

			/** 节点下是否有子节点	
			*/
			bool IsEmpty(const std::string& xpath);

		// private:
			TiXmlDocument * xmlDoc_;
			TiXmlElement* xmlRoot_;
			std::string filename_;

			static const std::string::size_type npos = -1;

		private:
			xml(const xml&);
			xml operator=(const xml&);
		};
	} // namespace helper

#endif

