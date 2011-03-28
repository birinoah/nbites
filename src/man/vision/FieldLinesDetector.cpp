#include "FieldLinesDetector.h"

using namespace std;
using boost::shared_ptr;

FieldLinesDetector::FieldLinesDetector(shared_ptr<Profiler> p) :
    VisualDetector(), edges(p), hough(p), gradient(new Gradient()),
    houghLines()
{

}

/**
 * Detect field lines and their intersections (aka corners) in the given image
 */
void FieldLinesDetector::detect(int upperBound, const uint16_t *img)
{
    // For safety (in case horizon is too low), scan from above the
    // given upperbound
    upperBound -= 10;

    // Only use values within the image
    upperBound = min(max(0, upperBound), IMAGE_HEIGHT-3);

    findHoughLines(upperBound, img);
    findFieldLines();
}

/**
 * Computes the gradient over the Y Channel of the image and
 * runs a hough transform to find all the pairs of hough space lines
 * in an image.
 *
 * Side effects: Updates gradient with current image's gradient values,
 *               updates list of hough space lines
 */
void FieldLinesDetector::findHoughLines(int upperBound, const uint16_t *img)
{
    edges.detectEdges(upperBound, img, gradient);
    houghLines = hough.findLines(gradient);
}

/**
 * Using the found hough lines and the gradient image, find the actual
 * field lines in the image.
 */
void FieldLinesDetector::findFieldLines()
{

}

void FieldLinesDetector::setEdgeThreshold(int thresh)
{
    edges.setThreshold(static_cast<uint8_t>(thresh));
}

void FieldLinesDetector::setHoughAcceptThreshold(int thresh)
{
    hough.setAcceptThreshold(thresh);
}
