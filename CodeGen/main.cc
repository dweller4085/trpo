#include "common.hh"

namespace ml {
    struct Construct {
        virtual ~Construct() = 0;
        virtual operator std::string () const = 0;
    };

    struct Item : Construct {};
    struct Statement : Construct {};
    constexpr int ident = 4;

    struct ClassDecl : Item {
        enum class AccessSpecifier {
            Public,
            Private,
            Protected,
        };

        virtual void addItem (std::pair<AccessSpecifier, shared_ptr<Construct>>) = 0;

        std::string name;
        std::vector <std::pair<AccessSpecifier, shared_ptr<Construct>>> body;
    };

    struct MethodDefDecl : Construct {
        enum class Specifier : int {
            Static = 1 << 0,
            Const = 1 << 1,
            Virtual = 1 << 2,
        };

        struct Signature {
            std::string name;
            std::vector<std::string> args;
            std::string returnType;
            int specifiers;
        };
        
        virtual void addStatement (shared_ptr<Statement>) = 0;

        Signature sig;
        std::vector<shared_ptr<Statement>> body;
    };

    struct PrintStatement : Statement {
        std::string text;
    };

    struct Program {
        void addItem (shared_ptr<Item>);
        operator std::string () const;

        std::vector<shared_ptr<Item>> body;
    };

    struct Factory {
        virtual shared_ptr<ClassDecl> createClassDecl (std::string const & name) = 0;
        virtual shared_ptr<MethodDefDecl> createMethodDefDecl (MethodDefDecl::Signature const & sig) = 0;
        virtual shared_ptr<PrintStatement> createPrintStatement (std::string const & text) = 0;
    };
}

namespace cc {
    struct PrintStatement final : ml::PrintStatement {
        explicit PrintStatement (std::string const & text) {
            ml::PrintStatement::text = text;
        }

        virtual operator std::string () const override {
            return std::string {} + "std::cout << \"" + self.text + "\" << \"\\n\";";
        }
    };


    struct ClassDecl final : ml::ClassDecl {
        explicit ClassDecl (std::string const & name) {
            ml::ClassDecl::name = name;
        }

        virtual void addItem (std::pair<AccessSpecifier, shared_ptr<Construct>> item) override {
            self.body.push_back(item);
        }
    };

    struct MethodDefDecl final : ml::MethodDefDecl {

    };

    struct Factory final : ml::Factory {
        virtual shared_ptr<ml::ClassDecl> createClassDecl (std::string const & name) override {
            return std::make_shared<cc::ClassDecl> (name);
        }

        virtual shared_ptr<ml::MethodDefDecl> createMethodDefDecl (ml::MethodDefDecl::Signature const & sig) override {
            return std::make_shared<cc::MethodDefDecl> (sig);
        }

        virtual shared_ptr<ml::PrintStatement> createPrintStatement (std::string const & text) override {
            return std::make_shared<cc::PrintStatement> (text);
        }
    };

}

namespace java {

}

namespace cs {
    
}

std::string composeProgram(ml::Factory & factory) {
    /*
    let program = Program {};
    let aClass = factory.createClassDecl ("AClass");
    aClass.addItem(...);
    program.addItem(aClass);
    return (std::string) program;
    */
}


int main (int argc, char ** argv) {


    return {0};
}
