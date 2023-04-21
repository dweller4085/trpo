#pragma once
#include "common.hh"
#include <stdexcept>

namespace ml {
    struct Construct {
        virtual ~Construct() = default;
        virtual operator std::string () const = 0;
    };

    constexpr auto identSize = 4;

    /*
    struct Type : Construct {
        enum {
            Int,
            Void,
            String,
        };
    };
    */

    struct ClassDecl : Construct {
        enum class AccessSpecifier {
            Public,
            Private,
            Protected,
            __count,
        };

        using AccessMarkedItem = std::pair<AccessSpecifier, shared_ptr<Construct>>;

        void addItem (AccessMarkedItem item) {
            self.body.push_back(item);
        }

    protected:
        std::string name;
        std::vector <AccessMarkedItem> body;
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
            /*
            Signature (std::string name, std::vector<std::string> args, std::string returnType, int specifiers) :
                name {name},
                args {args},
                returnType {returnType},
                specifiers {specifiers}
            {
                if (
                    specifiers & (int) Specifier::Static &&
                    ((specifiers & (int) Specifier::Virtual) || (specifiers & (int) Specifier::Const))
                ) {
                    throw std::invalid_argument {"The Static specififer is orthogonal to all other method specifiers."};
                }
            }*/
        };

        void addStatement (shared_ptr<Construct> statement) {
            self.body.push_back(statement);
        }
    
    protected:
        Signature sig;
        std::vector<shared_ptr<Construct>> body;
    };

    struct PrintStatement : Construct {
    protected:
        std::string text;
    };

    struct Program {
        void addItem (shared_ptr<Construct> item) {
            self.body.push_back(item);
        }

        operator std::string () const {
            let program = std::string {};
            for (auto item : body) {
                program += (std::string)*item + "\n\n";
            }

            return std::move (program);
        }
    
    protected:
        std::vector<shared_ptr<Construct>> body;
    };

    struct Factory {
        virtual shared_ptr<ClassDecl> createClassDecl (std::string const & name) = 0;
        virtual shared_ptr<MethodDefDecl> createMethodDefDecl (MethodDefDecl::Signature const & sig) = 0;
        virtual shared_ptr<PrintStatement> createPrintStatement (std::string const & text) = 0;
    };
}

inline std::string ident (std::string const & in, int identSize = ml::identSize) {
    let s = std::string {in};
    size_t pos = 0;
    s.insert(pos, identSize, ' ');
    while ((pos = s.find("\n", pos + ml::identSize)) != std::string::npos) {
        s.insert(pos + 1, identSize, ' ');
    }

    return {std::move(s)};
}
