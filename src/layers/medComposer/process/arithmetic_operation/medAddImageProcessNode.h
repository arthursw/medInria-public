/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <dtkComposer>

#include <medAbstractAddImageProcess.h>

#include <medComposerExport.h>

class medAddImageProcessNodePrivate;

class MEDCOMPOSER_EXPORT medAddImageProcessNode : public dtkComposerNodeObject<medAbstractAddImageProcess>
{
public:
     medAddImageProcessNode(void);
    ~medAddImageProcessNode(void);

public:
    void run(void);

private:
    medAddImageProcessNodePrivate *d;
};