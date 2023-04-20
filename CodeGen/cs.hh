#pragma once
#include "ml.hh"
/*
namespace cs {
    struct PrintStatement final : ml::PrintStatement {

    };

    struct ClassDecl final : ml::ClassDecl {

    };

    struct MethodDefDecl final : ml::MethodDefDecl {

    };

    struct Factory final : ml::Factory {
        virtual shared_ptr<ml::ClassDecl> createClassDecl (std::string const & name) override {
            return std::make_shared<ClassDecl> (name);
        }

        virtual shared_ptr<ml::MethodDefDecl> createMethodDefDecl (ml::MethodDefDecl::Signature const & sig) override {
            return std::make_shared<MethodDefDecl> (sig);
        }

        virtual shared_ptr<ml::PrintStatement> createPrintStatement (std::string const & text) override {
            return std::make_shared<PrintStatement> (text);
        }
    };
}
*/