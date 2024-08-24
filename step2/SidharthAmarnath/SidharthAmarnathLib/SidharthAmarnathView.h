/**
 * @file SidharthAmarnathView.h
 * @author Sid Amarnath
 *
 * White window view class
 */

#ifndef SIDHARTHAMARNATH_SIDHARTHAMARNATHVIEW_H
#define SIDHARTHAMARNATH_SIDHARTHAMARNATHVIEW_H

class SidharthAmarnathView : public wxWindow {
private:
    void OnPaint(wxPaintEvent& event);

public:
    void Initialize(wxFrame* parent);

};

#endif //SIDHARTHAMARNATH_SIDHARTHAMARNATHVIEW_H
