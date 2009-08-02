#include "stdafx.h"
#include "TinyXmlHelper.hpp"

#ifndef _CRT_SECURE_NO_DEPRECATE
	#define _CRT_SECURE_NO_DEPRECATE
#endif

#ifndef TIXML_USE_STL
#define TIXML_USE_STL 1
#endif

//
#ifdef WIN32
	#pragma warning(disable:4996)
	#pragma warning(disable:4267)
#endif

//#pragma   push_macro("min")   
//#pragma   push_macro("max")   
//#undef   min   
//#undef   max   
//#include <random>
//#include <regex>
//#pragma   pop_macro("min")   
//#pragma   pop_macro("max")

#include "xpath_static.h"

#ifdef WIN32
#	ifdef _DEBUG
#		pragma comment(lib,"tinyxpathd.lib")
#	else
#		pragma comment(lib,"tinyxpath.lib")
#	endif
#endif

using namespace helper;

xml::xml(): xmlDoc_(new TiXmlDocument), xmlRoot_(0) 
{
}

xml::~xml()
{
	delete xmlDoc_;
}

bool xml::LoadFile(const std::string& filename)
{
	xmlDoc_->Clear();

	bool ret = xmlDoc_->LoadFile(filename.c_str());
	if(!ret)
	{
		return false;
	}
	xmlRoot_ = xmlDoc_->RootElement();
	if(xmlRoot_ == NULL)
		return false;

	filename_ = filename;

	return true;
}

bool xml::SaveFile()
{
	return xmlDoc_->SaveFile(filename_);
}

bool xml::SaveFile(const char* filename)
{
	return xmlDoc_->SaveFile(filename);
}

bool xml::SaveFile(const std::string& filename)
{
	return xmlDoc_->SaveFile(filename);
}

bool xml::LoadBuffer(const std::string& str)
{
	xmlDoc_->Clear();
	xmlDoc_->Parse(str.c_str());
	xmlRoot_ = xmlDoc_->RootElement();
	if(xmlRoot_ == NULL)
		return false;
	return true;
}



Pair xml::GetPair(const std::string& xpath)
{
	//using namespace std;
	//static tr1::regex  regexAttr("(.+/@\\w+$)");
	//static tr1::regex  regexNode("(^.+/\\w+$)");
	//// xpath指向一个属性结点
	//if(tr1::regex_match(xpath, regexAttr))
	//{
	//	return GetSingleAttr(xpath);
	//}
	//// xpath指向一个普通结点
	//else if(tr1::regex_match(xpath, regexNode))
	//{
	//	return GetSingleNode(xpath);
	//}
	//// 其它
	//else
	//	return ValuePair();

	if(xpath.rfind("/@") != npos)
	{
		return GetSingleAttr(xpath);
	}
	// xpath指向一个普通结点
	else if (xpath.rfind("/") != npos)
	{
		return GetSingleNode(xpath);
	}
	// 其它
	else
		return Pair();
}

std::string xml::GetValue(const std::string& xpath)
{
	if(xpath.rfind("/@") != npos)
	{
		return GetAttrValue(xpath);
	}
	// xpath指向一个普通结点
	else if (xpath.rfind("/") != npos)
	{
		return GetNodeValue(xpath);
	}
	// 其它
	else
		return "";
}

std::string xml::GetValue(const char* xpath)
{
	return GetValue(std::string(xpath));
}

Pair xml::GetSingleNode(const std::string& xpath)
{
	Pair p;
	TiXmlNode* node = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	if(node == NULL)
		return p;
	p.first = node->Value();
	TiXmlHandle h(node);
	TiXmlText* t = h.FirstChild().Text();
	if(t == NULL)
		return Pair();
	p.second = t->Value();
	return p;
}

std::string xml::GetNodeValue(const std::string& xpath)
{
	TiXmlNode* node = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	if(node == NULL)
		return "";
	TiXmlHandle h(node);
	TiXmlText* t = h.FirstChild().Text();
	if(t == NULL)
		return "";
	return t->Value();
}

std::string xml::GetNodeValue(const char* xpath)
{
	TiXmlNode* node = TinyXPath::XNp_xpath_node(xmlRoot_, xpath);
	if(node == NULL)
		return "";
	TiXmlHandle h(node);
	TiXmlText* t = h.FirstChild().Text();
	if(t == NULL)
		return "";
	return t->Value();
}

bool xml::SetNode(const std::string& xpath, const std::string& value)
{
	TiXmlNode* node = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	if(node == NULL)
		return false;
	node->SetValue(value);
	TiXmlHandle h(node);
	TiXmlText* t = h.FirstChild().Text();
	if(t == NULL)
		return false;
	t->SetValue(value);
	return true;
}

bool xml::SetNode(const char* xpath, const char* value)
{
	TiXmlNode* node = TinyXPath::XNp_xpath_node(xmlRoot_, xpath);
	if(node == NULL)
		return false;
	TiXmlHandle h(node);
	TiXmlText* t = h.FirstChild().Text();
	if(t == NULL)
		return false;
	t->SetValue(value);
	return true;
}

Pair xml::GetSingleAttr(const std::string& xpath)
{
	Pair p;
	TiXmlAttribute* attr = TinyXPath::XAp_xpath_attribute(xmlRoot_, xpath.c_str());
	if(attr == NULL)
		return p;
	p.first = attr->Name();
	p.second = attr->Value();
	return p;
}

std::string xml::GetAttrValue(const std::string& xpath)
{
	TiXmlAttribute* attr = TinyXPath::XAp_xpath_attribute(xmlRoot_, xpath.c_str());
	if(attr == NULL)
		return "";
	return attr->Value();
}

std::string xml::GetAttrValue(const char* xpath)
{
	TiXmlAttribute* attr = TinyXPath::XAp_xpath_attribute(xmlRoot_, xpath);
	if(attr == NULL)
		return "";
	return attr->Value();
}

bool xml::SetAttr(const std::string& xpath, const std::string& value)
{
	TiXmlAttribute* attr = TinyXPath::XAp_xpath_attribute(xmlRoot_,  xpath.c_str());
	if(attr == NULL)
		return false;	
	attr->SetValue(value);
	return true;
}

bool xml::SetAttr(const char* xpath, const char* value)
{
	TiXmlAttribute* attr = TinyXPath::XAp_xpath_attribute(xmlRoot_,  xpath);
	if(attr == NULL)
		return false;	
	attr->SetValue(value);
	return true;
}

PairSet xml::GetTagAndTextOfChilds(const std::string& xpath)
{	
	PairSet v;
	TiXmlNode* node = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	if(node == NULL)
		return v;
	if(node->NoChildren())
		return v;
	TiXmlNode* subNode = NULL;
	while(1)
	{
		subNode = node->IterateChildren(subNode);
		if(subNode == NULL)
			break;
		//if(subNode->Type() != TiXmlNode::NodeType::ELEMENT)
		if(subNode->Type() != TiXmlNode::ELEMENT)
			continue;
		Pair p;
		p.first = subNode->Value();
		TiXmlHandle h(subNode);
		TiXmlText* t = h.FirstChild().Text();
		if(t == NULL)
			return PairSet();
		p.second = t->Value();
		v.push_back(p);
	}
	return v;
}

PairSet xml::GetKeyAndTextOfChilds(const std::string& xpath, const std::string& attrName)
{
	PairSet v;
	TiXmlNode* node = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	if(node == NULL)
		return v;
	if(node->NoChildren())
		return v;
	TiXmlNode* subNode = NULL;
	while(1)
	{
		subNode = node->IterateChildren(subNode);
		if(subNode == NULL)
			break;
		//if(subNode->Type() != TiXmlNode::NodeType::ELEMENT)
		if(subNode->Type() != TiXmlNode::ELEMENT)
			continue;

		TiXmlAttribute* attr = NULL;
		std::string attrXPath = std::string("@") + attrName;
		attr = TinyXPath::XAp_xpath_attribute(subNode, attrXPath.c_str());
		if(attr == NULL)
			continue;
		
		Pair p;
		p.first = attr->Value();
		TiXmlHandle h(subNode);
		TiXmlText* t = h.FirstChild().Text();
		if(t == NULL)
			return PairSet();
		p.second = t->Value();
		v.push_back(p);
	}
	return v;
}

PairSetSet xml::GetAttrsOfChilds(const std::string& xpath)
{
	PairSetSet m;
	TiXmlNode* node = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	if(node == NULL)
		return m;
	if(node->NoChildren())
		return m;
	TiXmlNode* subNode = NULL;
	while(1)
	{
		subNode = node->IterateChildren(subNode);
		if(subNode == NULL)
			break;
		//if(subNode->Type() != TiXmlNode::NodeType::ELEMENT)
		if(subNode->Type() != TiXmlNode::ELEMENT)
			continue;

		PairSet v;
		// 得到结点名及其内容
		Pair p;
		p.first = subNode->Value();
		TiXmlHandle h(subNode);
		TiXmlText* t = h.FirstChild().Text();
		if(t == NULL)
			p.second = "";
		else
			p.second = t->Value();
		v.push_back(p);
		TiXmlAttribute* attr = NULL;
		// 得到结点属性
		attr = TinyXPath::XAp_xpath_attribute(subNode, "@*");
		if(attr != NULL)
		{
			v.push_back(Pair(attr->Name(), attr->Value()));
			while(1)
			{
				attr = attr->Next();
				if(attr != NULL)
				{
					v.push_back(Pair(attr->Name(), attr->Value()));
				}
				else
					break;
			}
		}
		m.push_back(v);
	}
	return m;
}


bool xml::InsertNode(const std::string& xpath, const std::string& text)
{
	TiXmlElement addThis("");
	//addThis.Parse(text.c_str(), NULL, TiXmlEncoding::TIXML_ENCODING_UTF8);
	addThis.Parse(text.c_str(), NULL, TIXML_ENCODING_UNKNOWN);
	TiXmlNode * afterThis = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	if (afterThis)
	{
		//TiXmlNode* c = afterThis->LastChild();
		//TiXmlNode* n = afterThis->InsertAfterChild(c, addThis);
		//注释的两句当<tag></tag>之间没有内容时会失败

		TiXmlNode* n = afterThis->InsertEndChild(addThis);
		if (n)
		{
			return true;
		}
	}
	return false;	
}

bool xml::RemoveNode(const std::string& xpath)
{
	TiXmlNode * removeThis = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	if (removeThis)
	{
		return removeThis->Parent()->RemoveChild(removeThis);
	}	
	return false;
}

bool xml::RemoveNodes(const std::string& xpath)
{
	TiXmlNode * removeThis = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	while(removeThis)
	{
		if(!removeThis->Parent()->RemoveChild(removeThis))
			return false;
		removeThis = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	}	
	
	return true;
}

bool xml::ClearNode(const std::string& xpath)
{
	TiXmlNode * node = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	if(node)
	{
		node->Clear();
		return true;
	}
	return false;	
}

bool xml::IsEmpty(const std::string& xpath)
{
	TiXmlNode * node = TinyXPath::XNp_xpath_node(xmlRoot_, xpath.c_str());
	if (!node->FirstChild())
	{
		return true;
	}
	return false;
}