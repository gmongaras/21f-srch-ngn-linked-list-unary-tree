#ifndef INC_21F_FINAL_PROJ_TEMPLATE_MYDOCUMENT_H
#define INC_21F_FINAL_PROJ_TEMPLATE_MYDOCUMENT_H


#include "rapidjson/document.h"
#include <string>
using namespace rapidjson;


//  myDocument inherits from GenericDocument to overwrite some of the functions
template <typename Encoding, typename Allocator = RAPIDJSON_DEFAULT_ALLOCATOR, typename StackAllocator = RAPIDJSON_DEFAULT_STACK_ALLOCATOR >
class myDocument: public GenericDocument<Encoding, Allocator, StackAllocator> {
public:
    typedef typename Encoding::Ch Ch;                       //!< Character type derived from Encoding.
    typedef GenericValue<Encoding, Allocator> ValueType;    //!< Value type of the document.
    typedef Allocator AllocatorType;                        //!< Allocator type from template parameter.


private:
    void ClearStack() {
        if (Allocator::kNeedFree)
            while (stack_.GetSize() > 0)    // Here assumes all elements in stack array are GenericValue (Member is actually 2 GenericValue objects)
                (stack_.template Pop<ValueType>(1))->~ValueType();
            else
                stack_.Clear();
            stack_.ShrinkToFit();
    }

    void Destroy() {
        RAPIDJSON_DELETE(ownAllocator_);
    }

    static const size_t kDefaultStackCapacity = 1024;
    Allocator* allocator_;
    Allocator* ownAllocator_;
    internal::Stack<StackAllocator> stack_;
    ParseResult parseResult_;

    // clear stack on any exit from ParseStream, e.g. due to exception
    struct ClearStackOnExit {
        explicit ClearStackOnExit(GenericDocument<Encoding, Allocator, StackAllocator> & d) : d_(d) {}
        ~ClearStackOnExit() { d_.ClearStack(); }
    private:
        ClearStackOnExit(const ClearStackOnExit&);
        ClearStackOnExit& operator=(const ClearStackOnExit&);
        GenericDocument<Encoding, Allocator, StackAllocator> & d_;
    };


public:
    //! Parse JSON text from an input stream (with Encoding conversion)
    /*! \tparam parseFlags Combination of \ref ParseFlag.
        \tparam SourceEncoding Encoding of input stream
        \tparam InputStream Type of input stream, implementing Stream concept
        \param is Input stream to be parsed.
        \return The document itself for fluent API.
    */
    template <unsigned parseFlags, typename SourceEncoding, typename InputStream>
    GenericDocument<Encoding, Allocator, StackAllocator>& ParseStream(InputStream& is, AVLTree<std::string>* AVL) {
        GenericReader<SourceEncoding, Encoding, StackAllocator> reader(
                stack_.HasAllocator() ? &stack_.GetAllocator() : 0);
        ClearStackOnExit scope(*this);
        parseResult_ = reader.template Parse<parseFlags>(is, *this);
        if (parseResult_) {
            RAPIDJSON_ASSERT(stack_.GetSize() == sizeof(ValueType)); // Got one and only one root object
            ValueType::operator=(*stack_.template Pop<ValueType>(1));// Move value from stack to document
        }
        return *this;
    }



    //! Parse JSON text from an input stream (with \ref kParseDefaultFlags)
    /*! \tparam InputStream Type of input stream, implementing Stream concept
        \param is Input stream to be parsed.
        \param AVL The AVL tree to add items to
        \return The document itself for fluent API.
    */
    template <typename InputStream>
    GenericDocument<Encoding, Allocator, StackAllocator>& ParseStream(InputStream& is, AVLTree<std::string>* AVL) {
        return ParseStream<kParseDefaultFlags, Encoding, InputStream>(is, AVL);
    }
};



#endif //INC_21F_FINAL_PROJ_TEMPLATE_MYDOCUMENT_H
