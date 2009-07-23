#ifndef __INFO_FRAME_H__
#define __INFO_FRAME_H__

#include <boost/tuple/tuple.hpp>
#include <vector>
#include "common.h"


class InfoFrame : public Gtk::Frame
{
public:
    InfoFrame();

private:
    LabelPtrArray key_label_arr;
    EntryPtrArray alias_entry_arr;
    EntryPtrArray value_entry_arr;
};

#endif 
