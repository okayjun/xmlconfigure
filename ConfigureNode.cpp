#include <ConfigureNode.h>

namespace xc{

    const char get_only_policy[] = "get_only_policy";

    const char create_only_policy[] = "create_only_policy";

    const char get_or_create_policy[] = "get_or_create_policy";

    const char policy_apply_on_node[] = "policy_apply_on_node";

    const char policy_apply_on_attr[] = "policy_apply_on_attr";

    configure_node::configure_node(){
        _name = "";
        _text = "";
    }

    configure_node::configure_node(const std::string& name,const std::string& text){
        _name = name;
        _text = text;
    }

    configure_node::configure_node(const configure_node& node){
        _name = node._name;
        _text = node._text;
        _children.assign(node._children.begin(), node._children.end());
    }

    configure_node& configure_node::operator=(const configure_node& node){
        _name = node._name;
        _text = node._text;
        _children.assign(node._children.begin(), node._children.end());
        return *this;
    }

    configure_node::~configure_node(){

    }

    const std::string& configure_node::text()const{
        return _text;
    }

    void configure_node::set_text(const std::string& name){
        _text = name;
    }

    const std::string& configure_node::name()const{
        return _name;
    }

    void configure_node::set_name(const std::string& name){
        _name = name;
    }

    configure_node* configure_node::get_node(const std::string& name){
        configure_node_list::iterator itr = _children.begin();
        if (itr->name() == name){
            return &_children[itr - _children.begin()];
        }
        return NULL;
    }

    configure_node* configure_node::create_node(const std::string& name){
        _children.push_back(configure_node(name));
        return &(_children[_children.size() - 1]);
    }

    configure_node* configure_node::get_or_create_node(const std::string& name){
        configure_node* node = get_node(name);
        if (NULL == node){
            node = create_node(name);
        }
        return node;
    }

    configure_variant* configure_node::get_attr(const std::string& name){
        if ( 0 == _field.count(name)){
            return NULL;
        }
        return &_field[name];
    }

    configure_variant* configure_node::create_attr(const std::string& name){
        _field[name] = configure_variant();
        return &_field[name];
    }

    configure_variant* configure_node::get_or_create_attr(const std::string& name){
        configure_variant* attr = get_attr(name);
        if (NULL == attr){
            attr = create_attr(name);
        }
        return attr;
    }

}