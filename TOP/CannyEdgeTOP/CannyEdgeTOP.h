/* Shared Use License: This file is owned by Derivative Inc. (Derivative)
* and can only be used, and/or modified for use, in conjunction with
* Derivative's TouchDesigner software, and only if you are a licensee who has
* accepted Derivative's TouchDesigner license or assignment agreement
* (which also govern the use of this file). You may share or redistribute
* a modified version of this file provided the following conditions are met:
*
* 1. The shared file or redistribution must retain the information set out
* above and this list of conditions.
* 2. Derivative's name (Derivative Inc.) or its trademarks may not be used
* to endorse or promote products derived from this file without specific
* prior written permission from Derivative.
*/

#ifndef __CannyEdgeTOP__
#define __CannyEdgeTOP__

#include "TOP_CPlusPlusBase.h"

#include <opencv2\core.hpp>
#include <string>

namespace cv
{
	namespace cuda
	{
		class GpuMat;
	}
}

namespace GpuUtils
{
	enum class ChannelFormat;
}

struct Parameters;

/*
This example implements a TOP exposing the canny edge detector using openCV's cuda functionallity.

It takes the following parameters:
		- Low Threshold:    First threshold for the hysteresis procedure.
		- High Threshold:   Second threshold for the hysteresis procedure.
		- Aperture size:    Aperture size for the Sobel operator.
		- L2 Gradient:  If On, a more accurate norm should be used to compute the image gradient.
For more information visit: https://docs.opencv.org/3.4/d0/d05/group__cudaimgproc.html#gabc17953de36faa404acb07dc587451fc

This TOP takes one input which must be 8 bit single channel.
*/

// To get more help about these functions, look at TOP_CPlusPlusBase.h
class CannyEdgeTOP : public TOP_CPlusPlusBase
{
public:
    CannyEdgeTOP(const OP_NodeInfo *info);
    virtual ~CannyEdgeTOP();

    virtual void		getGeneralInfo(TOP_GeneralInfo*, const OP_Inputs*, void* reserved) override;

    virtual bool		getOutputFormat(TOP_OutputFormat*, const OP_Inputs*, void* reserved) override;

    virtual void		execute(TOP_OutputFormatSpecs*, const OP_Inputs*, TOP_Context*, void* reserved) override;

	virtual void		setupParameters(OP_ParameterManager*, void* reserved) override;

	virtual void		getErrorString(OP_String*, void* reserved) override;

private:
    void                handleParameters(const OP_Inputs*);

    void                inputTopToMat(const OP_TOPInput*);

	void 				cvMatToOutput(TOP_OutputFormatSpecs*) const;

	bool				checkInputTop(const OP_TOPInput*);


	cv::cuda::GpuMat*	myFrame;

	Parameters*			myParms;
	std::string			myError;

	int					myNumChan;
	int					myMatType;
	int					myPixelSize;
};

#endif
