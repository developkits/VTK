/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkIntPoints.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


Copyright (c) 1993-1998 Ken Martin, Will Schroeder, Bill Lorensen.

This software is copyrighted by Ken Martin, Will Schroeder and Bill Lorensen.
The following terms apply to all files associated with the software unless
explicitly disclaimed in individual files. This copyright specifically does
not apply to the related textbook "The Visualization Toolkit" ISBN
013199837-4 published by Prentice Hall which is covered by its own copyright.

The authors hereby grant permission to use, copy, and distribute this
software and its documentation for any purpose, provided that existing
copyright notices are retained in all copies and that this notice is included
verbatim in any distributions. Additionally, the authors grant permission to
modify this software and its documentation for any purpose, provided that
such modifications are not distributed without the explicit consent of the
authors and that existing copyright notices are retained in all copies. Some
of the algorithms implemented by this software are patented, observe all
applicable patent law.

IN NO EVENT SHALL THE AUTHORS OR DISTRIBUTORS BE LIABLE TO ANY PARTY FOR
DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
OF THE USE OF THIS SOFTWARE, ITS DOCUMENTATION, OR ANY DERIVATIVES THEREOF,
EVEN IF THE AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE AUTHORS AND DISTRIBUTORS SPECIFICALLY DISCLAIM ANY WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE IS PROVIDED ON AN
"AS IS" BASIS, AND THE AUTHORS AND DISTRIBUTORS HAVE NO OBLIGATION TO PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.


=========================================================================*/
#include "vtkIntPoints.h"

vtkIntPoints::vtkIntPoints()
{
  this->P = vtkIntArray::New();
}

vtkIntPoints::vtkIntPoints(const vtkIntPoints& ss)
{
  this->P = vtkIntArray::New();
  *(this->P) = *(ss.P);
}

vtkIntPoints::vtkIntPoints(const int sz, const int ext)
{
  this->P = vtkIntArray::New();
  this->P->Allocate(sz*3,ext*3);
}

vtkIntPoints::~vtkIntPoints()
{
  this->P->Delete();
}

vtkPoints *vtkIntPoints::MakeObject(int sze, int ext)
{
  return new vtkIntPoints(sze,ext);
}

// Description:
// Deep copy of points.
vtkIntPoints& vtkIntPoints::operator=(const vtkIntPoints& fp)
{
  *(this->P) = *(fp.P);
  return *this;
}

float *vtkIntPoints::GetPoint(int i)
{
  static float x[3];
  int *iptr = this->P->GetPointer(3*i);
  x[0] = (float)iptr[0]; x[1] = (float)iptr[1]; x[2] = (float)iptr[2];
  return x;
};

void vtkIntPoints::GetPoints(vtkIdList& ptId, vtkFloatPoints& fp)
{
  for (int i=0; i<ptId.GetNumberOfIds(); i++)
    {
    fp.InsertPoint(i,this->GetPoint(ptId.GetId(i)));
    }
}
