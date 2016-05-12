#ifndef XML_CONFIGURE_NODE_HH
#define XML_CONFIGURE_NODE_HH
#include <Export.h>
#include <map>
#include <ConfigureVariant.h>

namespace xc{
    
    /**
     *
     */
    extern const char get_only_policy[];

    /**
     *
     */
    extern const char create_only_policy[];

    /**
     *
     */
    extern const char get_or_create_policy[];

    /**
     *
     */
    extern const char policy_apply_on_node[];

    /**
     *
     */
    extern const char policy_apply_on_attr[];

    /**
     *
     */
    class configure_node;

    /**
     *
     */
    typedef std::map<std::string, configure_variant> configure_node_attribute_set;

    /**
     *
     */
    typedef std::vector<configure_node> configure_node_list;

    /**
     *
     */
    template<const char apply[], const char policy[]>
    struct policy_result_type {
        typedef typename void* result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_node, get_only_policy>{
        typedef  configure_node& result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_attr, get_only_policy>{
        typedef  configure_variant& result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_node, create_only_policy>{
        typedef  configure_node& result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_attr, create_only_policy>{
        typedef  configure_variant& result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_node, get_or_create_policy>{
        typedef  configure_node& result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_attr, get_or_create_policy>{
        typedef  configure_variant& result_type;
    };

    /**
     *
     */
    template<const char apply[], const char policy[]>
    class visit_policy{
        typename policy_result_type<apply, policy>::result_type
            operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    class visit_policy<policy_apply_on_node, get_only_policy>{
        policy_result_type<policy_apply_on_node, get_only_policy>::result_type
            operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    class visit_policy<policy_apply_on_attr, get_only_policy>{
        policy_result_type<policy_apply_on_attr, get_only_policy>::result_type
            operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    class visit_policy<policy_apply_on_node, create_only_policy>{
        policy_result_type<policy_apply_on_node, create_only_policy>::result_type
            operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    class visit_policy<policy_apply_on_attr, create_only_policy>{
        policy_result_type<policy_apply_on_attr, create_only_policy>::result_type
            operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    class visit_policy<policy_apply_on_node, get_or_create_policy>{
        policy_result_type<policy_apply_on_node, get_or_create_policy>::result_type
            operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    class visit_policy<policy_apply_on_attr, get_or_create_policy>{
        policy_result_type<policy_apply_on_attr, get_or_create_policy>::result_type
            operator()(configure_node& self, const std::string& name);
    };



    /**
     *
     */
    class configure_node{

        /**
         *
         */
    public:

        /**
         *
         */
        configure_node();

        /**
         *
         */
        configure_node(const std::string& name, const std::string& text = "");

        /**
         *
         */
        configure_node(const configure_node & node);

        /**
         *
         */
        configure_node& operator=(const configure_node& node);

        /**
         *
         */
        ~configure_node();

        /**
         *
         */
    public:

        /**
         *
         */
        const std::string& text()const;

        /**
         *
         */
        void set_text(const std::string& text);

        /**
         *
         */
        const std::string& name()const;

        /**
         *
         */
        void set_name(const std::string& name);

        /**
         *
         */
    public:

        /**
         *
         */
        template<const char policy[]>
        configure_variant& operator[](const char[]);

        /**
         *
         */
        template<const char policy[]>
        configure_variant& operator[](const std::string&);

        /**
         *
         */
    public:

        /**
         *
         */
        template<const char identity[]>
        configure_node_list fields();

        /**
         *
         */
        configure_node_list fields(const char identity[]);

        /**
         *
         */
        template<const char identity[], const char policy[]>
        configure_node& field();

        /**
         *
         */
        template<const char policy[]>
        configure_node& field(const char identity);

        /**
         *
         */
        template<const char attr_name[], typename policy>
        configure_variant& attr();

        /**
         *
         */
        template<const char name[], const char policy[]>
        configure_variant& attr();

        /**
         *
         */
        template< const char attr_name[]>
        configure_variant& attr();

        /**
         *
         */
    public:

        /**
         *
         */
        configure_node* get_node(const std::string& name);

        /**
         *
         */
        configure_node* create_node(const std::string& name);

        /**
         *
         */
        configure_node* get_or_create_node(const std::string& name);

        /**
         *
         */
        configure_variant* get_attr(const std::string& name);

        /**
         *
         */
        configure_variant* create_attr(const std::string& name);

        /**
         *
         */
        configure_variant* get_or_create_attr(const std::string& name);

        /**
         *
         */
    protected:

        /**
         *
         */
        std::map<std::string, configure_variant> _field;

        /**
         *
         */
        configure_node_list _children;

        /**
         *
         */
        std::string _name;

        /**
         *
         */
        std::string _text;
    };


    //=========================================================================
    //default policy
    //=========================================================================
    template<const char apply[], const char policy[]>
    typename policy_result_type<apply, policy>::result_type
        visit_policy<apply, policy>::
        operator()(configure_node& self, const std::string& name){
        typename policy_result_type<v_type, policy>::result_type result;
        return result;
    }

    //=========================================================================
    //get_only_policy , policy_apply_on_node
    //=========================================================================
    policy_result_type<policy_apply_on_node, get_only_policy >::result_type
        visit_policy<policy_apply_on_node, get_only_policy>::
        operator()(configure_node& self, const std::string& name){
        return *self.get_node(name);
    }

    //=========================================================================
    //get_only_policy , policy_apply_on_node
    //=========================================================================
    policy_result_type<policy_apply_on_attr, get_only_policy >::result_type
        visit_policy<policy_apply_on_attr, get_only_policy>::
        operator()(configure_node& self, const std::string& name){
        return *self.get_attr(name);
    }

    //=========================================================================
    //get_only_policy , policy_apply_on_node
    //=========================================================================
    policy_result_type<policy_apply_on_node, create_only_policy>::result_type
        visit_policy<policy_apply_on_node, create_only_policy>::
        operator()(configure_node& self, const std::string& name){
        return *self.create_node(name);
    }

    //=========================================================================
    //get_only_policy , policy_apply_on_node
    //=========================================================================
    policy_result_type<policy_apply_on_attr, create_only_policy>::result_type
        visit_policy<policy_apply_on_attr, create_only_policy>::
        operator()(configure_node& self, const std::string& name){
        return *self.create_attr(name);
    }

    //=========================================================================
    //get_only_policy , policy_apply_on_node
    //=========================================================================
    policy_result_type<policy_apply_on_node, get_or_create_policy>::result_type
        visit_policy<policy_apply_on_node, get_or_create_policy>::
        operator()(configure_node& self, const std::string& name){
        return *self.get_or_create_node(name);
    }

    //=========================================================================
    //get_only_policy , policy_apply_on_node
    //=========================================================================
    policy_result_type<policy_apply_on_attr, get_or_create_policy>::result_type
        visit_policy<policy_apply_on_attr, get_or_create_policy>::
        operator()(configure_node& self, const std::string& name){
        return *self.get_or_create_attr(name);
    }

    /**
     *
     */
    template<const char policy[]>
    configure_variant& configure_node::operator[](const char identity[]){
        return visit_policy<policy_apply_on_attr, policy>(*this, identity);
    }

    /**
     *
     */
    template<const char policy[]>
    configure_variant& configure_node::operator[](const std::string& identity){
        return visit_policy<policy_apply_on_attr, policy>(*this, identity);
    }

    /**
     *
     */
    template<const char identity[]>
    configure_node_list configure_node::fields(){
        configure_node_list cnl;
        configure_node_list::iterator itr = _children.begin();
        for (; itr != _children; itr++){
            if (itr->name() == identity){
                cnl.push_back(*itr);
            }
        }
        return cnl;
    }

    /**
     *
     */
    template<const char identity[],const char policy[]>
    configure_node& configure_node::field(){
        return visit_policy<policy_apply_on_node, policy>(*this, identity);
    }

    /**
     *
     */
    template<const char policy[]>
    configure_node& configure_node::field(const char identity){
        return visit_policy<policy_apply_on_node, policy>(identity);
    }

    /**
     *
     */
    template<const char identity[], typename policy>
    configure_variant& configure_node::attr(){
        return visit_policy<policy_apply_on_attr, policy>(*this, identity);
    }

    /**
     *
     */
    template<const char identity[], const char policy[]>
    configure_variant& configure_node::attr(){
        return visit_policy<policy_apply_on_attr, policy>(*this, identity);
    }

    /**
     *
     */
    template< const char identity[]>
    configure_variant& configure_node::attr(){
        return visit_policy<policy_apply_on_attr, policy>(*this, identity);
    }
}

#endif//XML_CONFIGURE_NODE_HH
