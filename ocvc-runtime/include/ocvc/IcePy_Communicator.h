// **********************************************************************
//
// Copyright (c) 2003-2011 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEPY_COMMUNICATOR_H
#define ICEPY_COMMUNICATOR_H

#include <Ice/CommunicatorF.h>
#include <ocvc/api.h>

namespace IcePy
{

extern PyTypeObject CommunicatorType;

OC_RUNTIME_API bool initCommunicator(PyObject*);

OC_RUNTIME_API Ice::CommunicatorPtr getCommunicator(PyObject*);

OC_RUNTIME_API PyObject* createCommunicator(const Ice::CommunicatorPtr&);
OC_RUNTIME_API PyObject* getCommunicatorWrapper(const Ice::CommunicatorPtr&);

}

extern "C" PyObject* IcePy_initialize(PyObject*, PyObject*);
extern "C" PyObject* IcePy_initializeWithProperties(PyObject*, PyObject*);
extern "C" PyObject* IcePy_initializeWithLogger(PyObject*, PyObject*);
extern "C" PyObject* IcePy_initializeWithPropertiesAndLogger(PyObject*, PyObject*);

#endif
