#ifndef __COMMON_UTIL_UTIL_HELPER_H__
#define __COMMON_UTIL_UTIL_HELPER_H__

#include "cocos2d.h"
#include "ui/UIHelper.h"

USING_NS_CC;
using namespace cocos2d::ui;

class UtilHelper : public Helper
{
public:
	UtilHelper();
	~UtilHelper();

	/**
	* Find a node with a specific tag from root node.
	* This search will be recursive throught all child nodes.
	* @param root      The be seached root node.
	* @param tag       The node tag.
	* @return node instance pointer.
	*/
	static Node* seekNodeByTag(Node* root, int tag);

	/**
	* Find a node with a specific name from root node.
	* This search will be recursive throught all child nodes.
	*
	* @param root      The be searched root node.
	* @param name      The node name.
	* @return node isntance pointer.
	*/
	static Node* seekNodeByName(Node* root, const std::string& name);

	/**
	* Find a node with a specific vecDirName from root node.
	* This search will be recursive throught all child nodes.
	*
	* @param root      The be searched root node.
	* @param vecDirName      The node vecDirName.
	* @return node isntance pointer.
	*/
	static Node* seekNodeByDirName(const std::vector<std::string>& vecDirName);

private:

};

#endif