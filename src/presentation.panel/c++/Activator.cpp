/*
 * Copyright (C) 2014 Moonlight Desktop Environment Team
 * Authors:
 * Alexis López Zubieta
 * This file is part of Moonlight Desktop Environment.
 *
 * Moonlight Desktop Environment is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Moonlight Desktop Environment is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Moonlight Desktop Environment. If not, see <http://www.gnu.org/licenses/>.
 */

#include "PanelImpl.h"
#include "SidePanel.h"
#include "WidgetsTracker.h"

#include "presentation.panel/Panel.h"
#include "panel/ISidePanel.h"

#include <usModuleActivator.h>
#include <usModuleContext.h>
#include <usServiceProperties.h>

#include <QDebug>
#include <QPointer>
#include <qt5/QtCore/qpointer.h>

US_USE_NAMESPACE
/**
 */
class Activator : public ModuleActivator {
private:

    /**
     * Implements ModuleActivator::Load().
     *
     * @param context the framework context for the module.
     */
    void Load(ModuleContext* context) {
        m_SidePanel = new SidePanel();
        context->RegisterService<ISidePanel>(m_SidePanel, ServiceProperties());

        m_Panel = new PanelImpl();
        context->RegisterService<presentation_panel::Panel>(m_Panel, ServiceProperties());

        m_Panel->show();

        m_PanelWidgetsTracker = new WidgetsTracker(context, m_Panel);
    }

    /**
     * Implements ModuleActivator::Unload().
     *
     * @param context the framework context for the module.
     */
    void Unload(ModuleContext* context) {
        delete (m_Panel);
        delete (m_PanelWidgetsTracker);
        delete (m_SidePanel);
    }

    PanelImpl *m_Panel;
    SidePanel *m_SidePanel;
    WidgetsTracker *m_PanelWidgetsTracker;
};
US_EXPORT_MODULE_ACTIVATOR(presentation_panel, Activator)
