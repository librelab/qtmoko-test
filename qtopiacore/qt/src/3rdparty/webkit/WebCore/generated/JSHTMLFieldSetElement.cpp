/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#include "JSHTMLFieldSetElement.h"

#include <wtf/GetPtr.h>

#include "HTMLFieldSetElement.h"
#include "HTMLFormElement.h"
#include "JSHTMLFormElement.h"

#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLFieldSetElement)

/* Hash table */

static const HashTableValue JSHTMLFieldSetElementTableValues[4] =
{
    { "form", DontDelete|ReadOnly, (intptr_t)jsHTMLFieldSetElementForm, (intptr_t)0 },
    { "willValidate", DontDelete|ReadOnly, (intptr_t)jsHTMLFieldSetElementWillValidate, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLFieldSetElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLFieldSetElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 7, JSHTMLFieldSetElementTableValues, 0 };
#else
    { 8, 7, JSHTMLFieldSetElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLFieldSetElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLFieldSetElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLFieldSetElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLFieldSetElementConstructorTableValues, 0 };
#endif

class JSHTMLFieldSetElementConstructor : public DOMObject {
public:
    JSHTMLFieldSetElementConstructor(ExecState* exec)
        : DOMObject(JSHTMLFieldSetElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSHTMLFieldSetElementPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValuePtr proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSHTMLFieldSetElementConstructor::s_info = { "HTMLFieldSetElementConstructor", 0, &JSHTMLFieldSetElementConstructorTable, 0 };

bool JSHTMLFieldSetElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLFieldSetElementConstructor, DOMObject>(exec, &JSHTMLFieldSetElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLFieldSetElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLFieldSetElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLFieldSetElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSHTMLFieldSetElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLFieldSetElementPrototype::s_info = { "HTMLFieldSetElementPrototype", 0, &JSHTMLFieldSetElementPrototypeTable, 0 };

JSObject* JSHTMLFieldSetElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSHTMLFieldSetElement>(exec, globalObject);
}

const ClassInfo JSHTMLFieldSetElement::s_info = { "HTMLFieldSetElement", &JSHTMLElement::s_info, &JSHTMLFieldSetElementTable, 0 };

JSHTMLFieldSetElement::JSHTMLFieldSetElement(PassRefPtr<Structure> structure, PassRefPtr<HTMLFieldSetElement> impl)
    : JSHTMLElement(structure, impl)
{
}

JSObject* JSHTMLFieldSetElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSHTMLFieldSetElementPrototype(JSHTMLFieldSetElementPrototype::createStructure(JSHTMLElementPrototype::self(exec, globalObject)));
}

bool JSHTMLFieldSetElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLFieldSetElement, Base>(exec, &JSHTMLFieldSetElementTable, this, propertyName, slot);
}

JSValuePtr jsHTMLFieldSetElementForm(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLFieldSetElement* imp = static_cast<HTMLFieldSetElement*>(static_cast<JSHTMLFieldSetElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->form()));
}

JSValuePtr jsHTMLFieldSetElementWillValidate(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLFieldSetElement* imp = static_cast<HTMLFieldSetElement*>(static_cast<JSHTMLFieldSetElement*>(asObject(slot.slotBase()))->impl());
    return jsBoolean(imp->willValidate());
}

JSValuePtr jsHTMLFieldSetElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSHTMLFieldSetElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValuePtr JSHTMLFieldSetElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSHTMLFieldSetElementConstructor>(exec);
}


}
