/**********************************************************************

Audacity: A Digital Audio Editor

TrackControls.h

Paul Licameli split from TrackPanel.cpp

**********************************************************************/

#ifndef __AUDACITY_TRACK_CONTROLS__
#define __AUDACITY_TRACK_CONTROLS__

#include "CommonTrackPanelCell.h"

class PopupMenuTable;
class Track;

class CloseButtonHandle;
class MenuButtonHandle;
class MinimizeButtonHandle;
class SelectButtonHandle;
class TrackSelectHandle;

class TrackControls /* not final */ : public CommonTrackPanelCell
{
public:
   explicit
   TrackControls( std::shared_ptr<Track> pTrack );

   virtual ~TrackControls() = 0;

protected:
   std::shared_ptr<Track> DoFindTrack() override;

   std::weak_ptr<Track> mwTrack;
};

class CommonTrackControls /* not final */ : public TrackControls
{
public:
   using TrackControls::TrackControls;

   // This is passed to the InitMenu() methods of the PopupMenuTable
   // objects returned by GetMenuExtension:
   struct InitMenuData
   {
   public:
      Track *pTrack;
      wxWindow *pParent;
      unsigned result;
   };

protected:
   // An override is supplied for derived classes to call through but it is
   // still marked pure virtual
   virtual std::vector<UIHandlePtr> HitTest
      (const TrackPanelMouseState &state,
       const AudacityProject *) override = 0;

   unsigned DoContextMenu
      (const wxRect &rect, wxWindow *pParent, wxPoint *pPosition) override;
   virtual PopupMenuTable *GetMenuExtension(Track *pTrack) = 0;

   std::weak_ptr<CloseButtonHandle> mCloseHandle;
   std::weak_ptr<MenuButtonHandle> mMenuHandle;
   std::weak_ptr<MinimizeButtonHandle> mMinimizeHandle;
   std::weak_ptr<SelectButtonHandle> mSelectButtonHandle;
   std::weak_ptr<TrackSelectHandle> mSelectHandle;
};

#endif
