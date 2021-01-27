/**
* If not stated otherwise in this file or this component's LICENSE
* file the following copyright and licenses apply:
*
* Copyright 2020 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/

#include "RDKShell.h"
#include <string>
#include <iostream>
#include <mutex>
#include <thread>
#include <rdkshell/compositorcontroller.h>
#include <rdkshell/application.h>
#include <interfaces/IMemory.h>

const short WPEFramework::Plugin::RDKShell::API_VERSION_NUMBER_MAJOR = 1;
const short WPEFramework::Plugin::RDKShell::API_VERSION_NUMBER_MINOR = 0;
const string WPEFramework::Plugin::RDKShell::SERVICE_NAME = "org.rdk.RDKShell";
//methods
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_MOVE_TO_FRONT = "moveToFront";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_MOVE_TO_BACK = "moveToBack";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_MOVE_BEHIND = "moveBehind";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SET_FOCUS = "setFocus";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_KILL = "kill";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_ADD_KEY_INTERCEPT = "addKeyIntercept";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_REMOVE_KEY_INTERCEPT = "removeKeyIntercept";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_ADD_KEY_LISTENER = "addKeyListener";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_REMOVE_KEY_LISTENER = "removeKeyListener";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_ADD_KEY_METADATA_LISTENER = "addKeyMetadataListener";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_REMOVE_KEY_METADATA_LISTENER = "removeKeyMetadataListener";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_INJECT_KEY = "injectKey";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GENERATE_KEYS = "generateKey";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_SCREEN_RESOLUTION = "getScreenResolution";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SET_SCREEN_RESOLUTION = "setScreenResolution";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_CREATE_DISPLAY = "createDisplay";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_CLIENTS = "getClients";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_Z_ORDER = "getZOrder";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_BOUNDS = "getBounds";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SET_BOUNDS = "setBounds";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_VISIBILITY = "getVisibility";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SET_VISIBILITY = "setVisibility";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_OPACITY = "getOpacity";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SET_OPACITY = "setOpacity";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_SCALE = "getScale";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SET_SCALE = "setScale";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_HOLE_PUNCH = "getHolePunch";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SET_HOLE_PUNCH = "setHolePunch";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_LOG_LEVEL = "getLogLevel";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SET_LOG_LEVEL = "setLogLevel";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_HIDE_SPLASH_LOGO = "hideSplashLogo";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_REMOVE_ANIMATION = "removeAnimation";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_ADD_ANIMATION = "addAnimation";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_ENABLE_INACTIVITY_REPORTING = "enableInactivityReporting";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SET_INACTIVITY_INTERVAL = "setInactivityInterval";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SCALE_TO_FIT = "scaleToFit";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_LAUNCH = "launch";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_LAUNCH_APP = "launchApplication";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SUSPEND = "suspend";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SUSPEND_APP = "suspendApplication";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_RESUME_APP = "resumeApplication";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_DESTROY = "destroy";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_AVAILABLE_TYPES = "getAvailableTypes";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_STATE = "getState";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_SYSTEM_MEMORY = "getSystemMemory";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_GET_SYSTEM_RESOURCE_INFO = "getSystemResourceInfo";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_SET_MEMORY_MONITOR = "setMemoryMonitor";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_LAUNCH_FACTORY_APP = "launchFactoryApp";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_LAUNCH_FACTORY_APP_SHORTCUT = "launchFactoryAppShortcut";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_LAUNCH_RESIDENT_APP = "launchResidentApp";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_METHOD_TOGGLE_FACTORY_APP = "toggleFactoryApp";

const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_USER_INACTIVITY = "onUserInactivity";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_APP_LAUNCHED = "onApplicationLaunched";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_APP_CONNECTED = "onApplicationConnected";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_APP_DISCONNECTED = "onApplicationDisconnected";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_APP_TERMINATED = "onApplicationTerminated";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_APP_FIRST_FRAME = "onApplicationFirstFrame";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_APP_SUSPENDED = "onApplicationSuspended";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_APP_RESUMED = "onApplicationResumed";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_APP_ACTIVATED = "onApplicationActivated";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_LAUNCHED = "onLaunched";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_SUSPENDED = "onSuspended";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_DESTROYED = "onDestroyed";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_DEVICE_LOW_RAM_WARNING = "onDeviceLowRamWarning";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_DEVICE_CRITICALLY_LOW_RAM_WARNING = "onDeviceCriticallyLowRamWarning";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_DEVICE_LOW_RAM_WARNING_CLEARED = "onDeviceLowRamWarningCleared";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_DEVICE_CRITICALLY_LOW_RAM_WARNING_CLEARED = "onDeviceCriticallyLowRamWarningCleared";
const string WPEFramework::Plugin::RDKShell::RDKSHELL_EVENT_ON_EASTER_EGG = "onEasterEgg";

using namespace std;
using namespace RdkShell;
extern int gCurrentFramerate;
bool receivedResolutionRequest = false;
unsigned int resolutionWidth = 1280;
unsigned int resolutionHeight = 720;
static std::string sToken;
std::shared_ptr<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement>> gSystemServiceConnection;
bool gSystemServiceEventsSubscribed = false;

#define ANY_KEY 65536
#define RDKSHELL_THUNDER_TIMEOUT 20000
#define RDKSHELL_POWER_TIME_WAIT 2.5
#define SYSTEM_SERVICE_CALLSIGN "org.rdk.System"

enum RDKShellLaunchType
{
    UNKNOWN = 0,
    CREATE,
    ACTIVATE,
    SUSPEND,
    RESUME
};

namespace WPEFramework {
    namespace Plugin {

        vector<std::string> gActivePlugins;

        std::map<std::string, PluginStateChangeData*> gPluginsEventListener;

        uint32_t getKeyFlag(std::string modifier)
        {
          uint32_t flag = 0;
          if (0 == modifier.compare("ctrl"))
          {
            flag = RDKSHELL_FLAGS_CONTROL;
          }
          else if (0 == modifier.compare("shift"))
          {
            flag = RDKSHELL_FLAGS_SHIFT;
          }
          else if (0 == modifier.compare("alt"))
          {
            flag = RDKSHELL_FLAGS_ALT;
          }
          return flag;
        }

        SERVICE_REGISTRATION(RDKShell, 1, 0);

        RDKShell* RDKShell::_instance = nullptr;
        std::mutex gRdkShellMutex;
        std::mutex gPluginDataMutex;

        std::mutex gLaunchMutex;
        int32_t gLaunchCount = 0;

        static std::thread shellThread;

        void RDKShell::MonitorClients::StateChange(PluginHost::IShell* service)
        {
            if (service)
            {
                PluginHost::IShell::state currentState(service->State());
                if (currentState == PluginHost::IShell::ACTIVATION)
                {
                   std::string configLine = service->ConfigLine();
                   if (configLine.empty())
                   {
                       return;
                   }
                   JsonObject serviceConfig = JsonObject(configLine.c_str());
                   if (serviceConfig.HasLabel("clientidentifier"))
                   {
                       std::string clientidentifier = serviceConfig["clientidentifier"].String();
                       gRdkShellMutex.lock();
                       RdkShell::CompositorController::createDisplay(service->Callsign(), clientidentifier);
                       RdkShell::CompositorController::addListener(clientidentifier, mShell.mEventListener);
                       gRdkShellMutex.unlock();
                       gPluginDataMutex.lock();
                       gActivePlugins.push_back(service->Callsign());
                       gPluginDataMutex.unlock();
                   }
                }
                else if (currentState == PluginHost::IShell::ACTIVATED && service->Callsign() == WPEFramework::Plugin::RDKShell::SERVICE_NAME)
                {
                   /* PluginHost::ISubSystem* subSystems(service->SubSystems());
                    if (subSystems != nullptr)
                    {
                        subSystems->Set(PluginHost::ISubSystem::PLATFORM, nullptr);
                        subSystems->Set(PluginHost::ISubSystem::GRAPHICS, nullptr);
                        subSystems->Release();
                    } */
                }
                else if (currentState == PluginHost::IShell::ACTIVATED && service->Callsign() == SYSTEM_SERVICE_CALLSIGN)
                {
                   std::string serviceCallsign = service->Callsign();
                   serviceCallsign.append(".1");
                   gSystemServiceConnection = getThunderControllerClient(serviceCallsign);
                }
                else if (currentState == PluginHost::IShell::DEACTIVATED)
                {
                    std::string configLine = service->ConfigLine();
                    if (configLine.empty())
                    {
                        return;
                    }
                    JsonObject serviceConfig = JsonObject(configLine.c_str());
                    if (serviceConfig.HasLabel("clientidentifier"))
                    {
                        std::string clientidentifier = serviceConfig["clientidentifier"].String();
                        gRdkShellMutex.lock();
                        RdkShell::CompositorController::kill(service->Callsign());
                        RdkShell::CompositorController::removeListener(clientidentifier, mShell.mEventListener);
                        gRdkShellMutex.unlock();
                    }
                    
                    gPluginDataMutex.lock();
                    std::vector<std::string>::iterator pluginToRemove = gActivePlugins.end();
                    for (std::vector<std::string>::iterator iter = gActivePlugins.begin() ; iter != gActivePlugins.end(); ++iter)
                    {
                      if ((*iter) == service->Callsign())
                      {
                        pluginToRemove = iter;
                        break;
                      }
                    }
                    if (pluginToRemove != gActivePlugins.end())
                    {
                      gActivePlugins.erase(pluginToRemove);
                    }
                    std::map<std::string, PluginStateChangeData*>::iterator pluginStateChangeEntry = gPluginsEventListener.find(service->Callsign());
                    if (pluginStateChangeEntry != gPluginsEventListener.end())
                    {
                        PluginStateChangeData* stateChangeData = pluginStateChangeEntry->second;
                        if (nullptr != stateChangeData)
                        {
                            delete stateChangeData;
                        }
                        pluginStateChangeEntry->second = nullptr;
                        gPluginsEventListener.erase(pluginStateChangeEntry);
                    }
                    gPluginDataMutex.unlock();
                }
            }
        }

        RDKShell::RDKShell()
                : AbstractPlugin(), mClientsMonitor(Core::Service<MonitorClients>::Create<MonitorClients>(this)), mEnableUserInactivityNotification(false), mCurrentService(nullptr)
        {
            LOGINFO("ctor");
            RDKShell::_instance = this;
            mEventListener = std::make_shared<RdkShellListener>(this);

            mRemoteShell = false;
            registerMethod(RDKSHELL_METHOD_MOVE_TO_FRONT, &RDKShell::moveToFrontWrapper, this);
            registerMethod(RDKSHELL_METHOD_MOVE_TO_BACK, &RDKShell::moveToBackWrapper, this);
            registerMethod(RDKSHELL_METHOD_MOVE_BEHIND, &RDKShell::moveBehindWrapper, this);
            registerMethod(RDKSHELL_METHOD_SET_FOCUS, &RDKShell::setFocusWrapper, this);
            registerMethod(RDKSHELL_METHOD_KILL, &RDKShell::killWrapper, this);
            registerMethod(RDKSHELL_METHOD_ADD_KEY_INTERCEPT, &RDKShell::addKeyInterceptWrapper, this);
            registerMethod(RDKSHELL_METHOD_REMOVE_KEY_INTERCEPT, &RDKShell::removeKeyInterceptWrapper, this);
            registerMethod(RDKSHELL_METHOD_ADD_KEY_LISTENER, &RDKShell::addKeyListenersWrapper, this);
            registerMethod(RDKSHELL_METHOD_REMOVE_KEY_LISTENER, &RDKShell::removeKeyListenersWrapper, this);
            registerMethod(RDKSHELL_METHOD_ADD_KEY_METADATA_LISTENER, &RDKShell::addKeyMetadataListenerWrapper, this);
            registerMethod(RDKSHELL_METHOD_REMOVE_KEY_METADATA_LISTENER, &RDKShell::removeKeyMetadataListenerWrapper, this);
            registerMethod(RDKSHELL_METHOD_INJECT_KEY, &RDKShell::injectKeyWrapper, this);
            registerMethod(RDKSHELL_METHOD_GENERATE_KEYS, &RDKShell::generateKeyWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_SCREEN_RESOLUTION, &RDKShell::getScreenResolutionWrapper, this);
            registerMethod(RDKSHELL_METHOD_SET_SCREEN_RESOLUTION, &RDKShell::setScreenResolutionWrapper, this);
            registerMethod(RDKSHELL_METHOD_CREATE_DISPLAY, &RDKShell::createDisplayWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_CLIENTS, &RDKShell::getClientsWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_Z_ORDER, &RDKShell::getZOrderWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_BOUNDS, &RDKShell::getBoundsWrapper, this);
            registerMethod(RDKSHELL_METHOD_SET_BOUNDS, &RDKShell::setBoundsWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_VISIBILITY, &RDKShell::getVisibilityWrapper, this);
            registerMethod(RDKSHELL_METHOD_SET_VISIBILITY, &RDKShell::setVisibilityWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_OPACITY, &RDKShell::getOpacityWrapper, this);
            registerMethod(RDKSHELL_METHOD_SET_OPACITY, &RDKShell::setOpacityWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_SCALE, &RDKShell::getScaleWrapper, this);
            registerMethod(RDKSHELL_METHOD_SET_SCALE, &RDKShell::setScaleWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_HOLE_PUNCH, &RDKShell::getHolePunchWrapper, this);
            registerMethod(RDKSHELL_METHOD_SET_HOLE_PUNCH, &RDKShell::setHolePunchWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_LOG_LEVEL, &RDKShell::getLogLevelWrapper, this);
            registerMethod(RDKSHELL_METHOD_SET_LOG_LEVEL, &RDKShell::setLogLevelWrapper, this);
            registerMethod(RDKSHELL_METHOD_HIDE_SPLASH_LOGO, &RDKShell::hideSplashLogoWrapper, this);
            registerMethod(RDKSHELL_METHOD_REMOVE_ANIMATION, &RDKShell::removeAnimationWrapper, this);
            registerMethod(RDKSHELL_METHOD_ADD_ANIMATION, &RDKShell::addAnimationWrapper, this);
            registerMethod(RDKSHELL_METHOD_ENABLE_INACTIVITY_REPORTING, &RDKShell::enableInactivityReportingWrapper, this);
            registerMethod(RDKSHELL_METHOD_SET_INACTIVITY_INTERVAL, &RDKShell::setInactivityIntervalWrapper, this);
            registerMethod(RDKSHELL_METHOD_SCALE_TO_FIT, &RDKShell::scaleToFitWrapper, this);
            registerMethod(RDKSHELL_METHOD_LAUNCH, &RDKShell::launchWrapper, this);
            registerMethod(RDKSHELL_METHOD_LAUNCH_APP, &RDKShell::launchApplicationWrapper, this);
            registerMethod(RDKSHELL_METHOD_SUSPEND, &RDKShell::suspendWrapper, this);
            registerMethod(RDKSHELL_METHOD_SUSPEND_APP, &RDKShell::suspendApplicationWrapper, this);
            registerMethod(RDKSHELL_METHOD_RESUME_APP, &RDKShell::resumeApplicationWrapper, this);
            registerMethod(RDKSHELL_METHOD_DESTROY, &RDKShell::destroyWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_AVAILABLE_TYPES, &RDKShell::getAvailableTypesWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_STATE, &RDKShell::getState, this);
            registerMethod(RDKSHELL_METHOD_GET_SYSTEM_MEMORY, &RDKShell::getSystemMemoryWrapper, this);
            registerMethod(RDKSHELL_METHOD_GET_SYSTEM_RESOURCE_INFO, &RDKShell::getSystemResourceInfoWrapper, this);
            registerMethod(RDKSHELL_METHOD_SET_MEMORY_MONITOR, &RDKShell::setMemoryMonitorWrapper, this);
            registerMethod(RDKSHELL_METHOD_LAUNCH_FACTORY_APP, &RDKShell::launchFactoryAppWrapper, this);
            registerMethod(RDKSHELL_METHOD_LAUNCH_FACTORY_APP_SHORTCUT, &RDKShell::launchFactoryAppShortcutWrapper, this);
            registerMethod(RDKSHELL_METHOD_LAUNCH_RESIDENT_APP, &RDKShell::launchResidentAppWrapper, this);
            registerMethod(RDKSHELL_METHOD_TOGGLE_FACTORY_APP, &RDKShell::toggleFactoryAppWrapper, this);
        }

        RDKShell::~RDKShell()
        {
            LOGINFO("dtor");
            mClientsMonitor->Release();
            RDKShell::_instance = nullptr;
            mRemoteShell = false;
            CompositorController::setEventListener(nullptr);
            mEventListener = nullptr;
            mEnableUserInactivityNotification = false;
            gActivePlugins.clear();
        }

        const string RDKShell::Initialize(PluginHost::IShell* service )
        {
            LOGINFO();

            std::cout << "initializing\n";

            mCurrentService = service;
            CompositorController::setEventListener(mEventListener);
#ifdef RFC_ENABLED
            RFC_ParamData_t param;
            bool ret = Utils::getRFCConfig("Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Power.UserInactivityNotification.Enable", param);
            if (true == ret && param.type == WDMP_BOOLEAN && (strncasecmp(param.value,"true",4) == 0))
            {
              mEnableUserInactivityNotification = true;
              enableInactivityReporting(true);
              ret = Utils::getRFCConfig("Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.Feature.Power.UserInactivityNotification.TimeMinutes", param);
              if (true == ret)
              {
                try
                {
                  CompositorController::setInactivityInterval(std::stod(param.value));
                }
                catch (...)
                { 
                  std::cout << "RDKShell unable to set inactivity interval  " << std::endl;
                }
              }
            }
#else
            mEnableUserInactivityNotification = true;
#endif

            service->Register(mClientsMonitor);

            static PluginHost::IShell* pluginService = nullptr;
            pluginService = service;

            shellThread = std::thread([]() {
                gRdkShellMutex.lock();
                RdkShell::initialize();
                PluginHost::ISubSystem* subSystems(pluginService->SubSystems());
                if (subSystems != nullptr)
                {
                    std::cout << "setting platform and graphics\n";
                    subSystems->Set(PluginHost::ISubSystem::PLATFORM, nullptr);
                    subSystems->Set(PluginHost::ISubSystem::GRAPHICS, nullptr);
                    subSystems->Release();
                }
                gRdkShellMutex.unlock();
                while(true) {
                  const double maxSleepTime = (1000 / gCurrentFramerate) * 1000;
                  double startFrameTime = RdkShell::microseconds();
                  gRdkShellMutex.lock();
                  if (receivedResolutionRequest)
                  {
                    CompositorController::setScreenResolution(resolutionWidth, resolutionHeight);
                    receivedResolutionRequest = false;
                  }
                  RdkShell::draw();
                  RdkShell::update();
                  gRdkShellMutex.unlock();
                  double frameTime = (int)RdkShell::microseconds() - (int)startFrameTime;
                  if (frameTime < maxSleepTime)
                  {
                      int sleepTime = (int)maxSleepTime-(int)frameTime;
                      usleep(sleepTime);
                  }
                }
            });

            service->Register(mClientsMonitor);
            Utils::SecurityToken::getSecurityToken(sToken);
            return "";
        }

        void RDKShell::Deinitialize(PluginHost::IShell* service)
        {
            LOGINFO();

            mCurrentService = nullptr;
            service->Unregister(mClientsMonitor);
        }

        string RDKShell::Information() const
        {
            return(string("{\"service\": \"") + SERVICE_NAME + string("\"}"));
        }

        std::shared_ptr<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement> > RDKShell::getThunderControllerClient(std::string callsign)
        {
            string query = "token=" + sToken;

            Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T("127.0.0.1:9998")));
            std::shared_ptr<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement> > thunderClient = make_shared<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement> >(callsign.c_str(), "",false, query);
            return thunderClient;
        }

        std::shared_ptr<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement>> RDKShell::getPackagerPlugin()
        {
            string query = "token=" + sToken;

            Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T("127.0.0.1:9998")));
            return make_shared<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement>>("Packager.1", "", false, query);
        }

        std::shared_ptr<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement>> RDKShell::getOCIContainerPlugin()
        {
            string query = "token=" + sToken;

            Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T("127.0.0.1:9998")));
            return make_shared<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement>>("org.rdk.OCIContainer.1", "", false, query);
        }

        void RDKShell::pluginEventHandler(const JsonObject& parameters)
        {
            std::string message;
            parameters.ToString(message);
            if (parameters.HasLabel("powerState"))
            {
                std::string powerState = parameters["powerState"].String();
                if ((powerState.compare("LIGHT_SLEEP") == 0) || (powerState.compare("DEEP_SLEEP") == 0))
                {
                    std::cout << "Received power state change to sleep " << std::endl;
                    JsonObject request, response;
                    uint32_t status = launchResidentAppWrapper(request, response);
                }
            }
        }

        void RDKShell::RdkShellListener::onApplicationLaunched(const std::string& client)
        {
          std::cout << "RDKShell onApplicationLaunched event received ..." << client << std::endl;
          JsonObject params;
          params["client"] = client;
          mShell.notify(RDKSHELL_EVENT_ON_APP_LAUNCHED, params);
        }

        void RDKShell::RdkShellListener::onApplicationConnected(const std::string& client)
        {
          std::cout << "RDKShell onApplicationConnected event received ..." << client << std::endl;
          JsonObject params;
          params["client"] = client;
          mShell.notify(RDKSHELL_EVENT_ON_APP_CONNECTED, params);
        }

        void RDKShell::RdkShellListener::onApplicationDisconnected(const std::string& client)
        {
          std::cout << "RDKShell onApplicationDisconnected event received ..." << client << std::endl;
          JsonObject params;
          params["client"] = client;
          mShell.notify(RDKSHELL_EVENT_ON_APP_DISCONNECTED, params);
        }

        void RDKShell::RdkShellListener::onApplicationTerminated(const std::string& client)
        {
          std::cout << "RDKShell onApplicationTerminated event received ..." << client << std::endl;
          JsonObject params;
          params["client"] = client;
          mShell.notify(RDKSHELL_EVENT_ON_APP_TERMINATED, params);
        }

        void RDKShell::RdkShellListener::onApplicationFirstFrame(const std::string& client)
        {
          std::cout << "RDKShell onApplicationFirstFrame event received ..." << client << std::endl;
          JsonObject params;
          params["client"] = client;
          mShell.notify(RDKSHELL_EVENT_ON_APP_FIRST_FRAME, params);
        }

        void RDKShell::RdkShellListener::onApplicationSuspended(const std::string& client)
        {
          std::cout << "RDKShell onApplicationSuspended event received for " << client << std::endl;
          JsonObject params;
          params["client"] = client;
          mShell.notify(RDKSHELL_EVENT_ON_APP_SUSPENDED, params);
        }

        void RDKShell::RdkShellListener::onApplicationResumed(const std::string& client)
        {
          std::cout << "RDKShell onApplicationResumed event received for " << client << std::endl;
          JsonObject params;
          params["client"] = client;
          mShell.notify(RDKSHELL_EVENT_ON_APP_RESUMED, params);
        }

        void RDKShell::RdkShellListener::onApplicationActivated(const std::string& client)
        {
            std::cout << "RDKShell onApplicationActivated event received for " << client << std::endl;
            JsonObject params;
            params["client"] = client;
            mShell.notify(RDKSHELL_EVENT_ON_APP_ACTIVATED, params);
        }

        void RDKShell::RdkShellListener::onUserInactive(const double minutes)
        {
          std::cout << "RDKShell onUserInactive event received ..." << minutes << std::endl;
          JsonObject params;
          params["minutes"] = std::to_string(minutes);
          mShell.notify(RDKSHELL_EVENT_ON_USER_INACTIVITY, params);
        }

        void RDKShell::RdkShellListener::onDeviceLowRamWarning(const int32_t freeKb)
        {
          std::cout << "RDKShell onDeviceLowRamWarning event received ..." << freeKb << std::endl;
          JsonObject params;
          params["ram"] = freeKb;
          mShell.notify(RDKSHELL_EVENT_DEVICE_LOW_RAM_WARNING, params);
        }

        void RDKShell::RdkShellListener::onDeviceCriticallyLowRamWarning(const int32_t freeKb)
        {
          std::cout << "RDKShell onDeviceCriticallyLowRamWarning event received ..." << freeKb << std::endl;
          JsonObject params;
          params["ram"] = freeKb;
          mShell.notify(RDKSHELL_EVENT_DEVICE_CRITICALLY_LOW_RAM_WARNING, params);
        }

        void RDKShell::RdkShellListener::onDeviceLowRamWarningCleared(const int32_t freeKb)
        {
          std::cout << "RDKShell onDeviceLowRamWarningCleared event received ..." << freeKb << std::endl;
          JsonObject params;
          params["ram"] = freeKb;
          mShell.notify(RDKSHELL_EVENT_DEVICE_LOW_RAM_WARNING_CLEARED, params);
        }

        void RDKShell::RdkShellListener::onDeviceCriticallyLowRamWarningCleared(const int32_t freeKb)
        {
          std::cout << "RDKShell onDeviceCriticallyLowRamWarningCleared event received ..." << freeKb << std::endl;
          JsonObject params;
          params["ram"] = freeKb;
          mShell.notify(RDKSHELL_EVENT_DEVICE_CRITICALLY_LOW_RAM_WARNING_CLEARED, params);
        }

        void RDKShell::RdkShellListener::onEasterEgg(const std::string& name, const std::string& actionJson)
        {
          std::cout << "RDKShell onEasterEgg event received ..." << name << std::endl;
          
          if (actionJson.length() == 0)
          {
            JsonObject params;
            params["name"] = name;
            mShell.notify(RDKSHELL_EVENT_ON_EASTER_EGG, params);
          }
          else
          {
            try
            {
              JsonObject actionObject = JsonObject(actionJson.c_str());
              if (actionObject.HasLabel("invoke"))
              {
                std::string invoke = actionObject["invoke"].String();
                size_t lastPositionOfDot = invoke.find_last_of(".");
                auto thunderController = getThunderControllerClient();
                if (lastPositionOfDot != -1)
                {
                    std::string callsign = invoke.substr(0, lastPositionOfDot);
                    std::cout << "callsign will be " << callsign << std::endl;
                    //get callsign
                    JsonObject activateParams;
                    activateParams.Set("callsign",callsign.c_str());
                    JsonObject activateResult;
                    int32_t activateStatus = thunderController->Invoke(3500, "activate", activateParams, activateResult);
                }

                std::cout << "invoking method " << invoke.c_str() << std::endl;
                JsonObject joResult;
                uint32_t status = 0;
                if (actionObject.HasLabel("params"))
                {
                  // setting wait Time to 2 seconds
                  gRdkShellMutex.unlock();
                  status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, invoke.c_str(), actionObject["params"], joResult);
                  gRdkShellMutex.lock();
                }
                else
                {
                  JsonObject joParams;
                  joParams["params"] = JsonObject();
                  // setting wait Time to 2 seconds
                  gRdkShellMutex.unlock();
                  status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, invoke.c_str(), joParams, joResult);
                  gRdkShellMutex.lock();
                }
                if (status > 0)
                {
                    std::cout << "failed to invoke " << invoke << "on easter egg.  status: " << status << std::endl;
                }
              }
            }
            catch(...)
            {
              std::cout << "error in parsing action for easter egg " << std::endl;
            }
          }
        }

        void RDKShell::RdkShellListener::onPowerKey()
        {
            static double lastPowerKeyTime = 0;
            double currentTime = RdkShell::seconds();
            double powerKeyTime = currentTime - lastPowerKeyTime;
            if (powerKeyTime < RDKSHELL_POWER_TIME_WAIT)
            {
                std::cout << "power key pressed too fast, ignoring " << powerKeyTime << std::endl;
            }
            JsonObject joGetParams;
            JsonObject joGetResult;
            joGetParams["params"] = JsonObject();
            std::string getPowerStateInvoke = "org.rdk.System.1.getPowerState";
            auto thunderController = getThunderControllerClient();
            uint32_t status = thunderController->Invoke(5000, getPowerStateInvoke.c_str(), joGetParams, joGetResult);

            std::cout << "get power state status: " << status << std::endl;

            if (status > 0)
            {
                std::cout << "error getting the power state\n";
                lastPowerKeyTime = RdkShell::seconds();
                return;
            }

            if (!joGetResult.HasLabel("powerState"))
            {
                std::cout << "the power state was not returned\n";
                lastPowerKeyTime = RdkShell::seconds();
                return;
            }

            const std::string currentPowerState = joGetResult["powerState"].String();
            std::cout << "the current power state is " << currentPowerState << std::endl;
            std::string newPowerState = "ON";
            if (currentPowerState == "ON")
            {
                newPowerState = "STANDBY";
            }

            JsonObject joSetParams;
            JsonObject joSetResult;
            joSetParams.Set("powerState",newPowerState.c_str());
            joSetParams.Set("standbyReason","power button pressed");
            std::string setPowerStateInvoke = "org.rdk.System.1.setPowerState";

            std::cout << "attempting to set the power state to " << newPowerState << std::endl;
            status = thunderController->Invoke(5000, setPowerStateInvoke.c_str(), joSetParams, joSetResult);
            std::cout << "get power state status second: " << status << std::endl;
            if (status > 0)
            {
                std::cout << "error setting the power state\n";
            }
            lastPowerKeyTime = RdkShell::seconds();
        }

        // Registered methods (wrappers) begin
        uint32_t RDKShell::moveToFrontWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                result = moveToFront(client);
                if (false == result) {
                  response["message"] = "failed to move front";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::moveToBackWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                result = moveToBack(client);
                if (false == result) {
                  response["message"] = "failed to move back";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::moveBehindWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (!parameters.HasLabel("target"))
            {
                result = false;
                response["message"] = "please specify target";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                const string target  = parameters["target"].String();
                result = moveBehind(client, target);
                if (false == result) {
                  response["message"] = "failed to move behind";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::setFocusWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                result = setFocus(client);
                if (false == result) {
                  response["message"] = "failed to set focus";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::killWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }

                // Get the client mime type
                std::string mimeType;
                getMimeType(client, mimeType);

                // Kill the display
                result = kill(client);
                if (!result)
                {
                    response["message"] = "failed to kill client";
                    returnResponse(false);
                }

                // App was a DAC app, so kill the container if it's still running
                if (mimeType == RDKSHELL_APPLICATION_MIME_TYPE_DAC_NATIVE)
                {
                    LOGINFO("Killing container");

                    auto ociContainerPlugin = getOCIContainerPlugin();
                    if (!ociContainerPlugin)
                    {
                        response["message"] = "OCIContainer plugin initialisation failed";
                        returnResponse(false);
                    }

                    JsonObject containerInfoResult;
                    JsonObject stopContainerResult;
                    JsonObject param;
                    param["containerId"] = client;

                    ociContainerPlugin->Invoke<JsonObject, JsonObject>(RDKSHELL_THUNDER_TIMEOUT, "getContainerInfo", param, containerInfoResult);

                    // If success is false, the container isn't running so nothing to do
                    if (containerInfoResult["success"].Boolean())
                    {
                        auto containerInfo = containerInfoResult["info"].Object();

                        // Dobby knows about that container - what's it doing?
                        if (containerInfo["state"] == "running" || containerInfo["state"] == "starting")
                        {
                            ociContainerPlugin->Invoke<JsonObject, JsonObject>(RDKSHELL_THUNDER_TIMEOUT, "stopContainer", param, stopContainerResult);
                        }
                        else if (containerInfo["state"] == "paused")
                        {
                            // Paused, so force stop
                            param["force"] = true;
                            ociContainerPlugin->Invoke<JsonObject, JsonObject>(RDKSHELL_THUNDER_TIMEOUT, "stopContainer", param, stopContainerResult);
                        }
                        else
                        {
                            response["message"] = "Container is not in a state that can be stopped";
                            returnResponse(false);
                        }

                        if (!stopContainerResult["success"].Boolean())
                        {
                            result = false;
                            response["message"] = "Failed to stop container";
                        }
                    }
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::addKeyInterceptWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            if (!parameters.HasLabel("keyCode"))
            {
                result = false;
                response["message"] = "please specify keyCode";
            }
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                //optional param?
                const JsonArray modifiers = parameters.HasLabel("modifiers") ? parameters["modifiers"].Array() : JsonArray();

                const uint32_t keyCode = parameters["keyCode"].Number();
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                result = addKeyIntercept(keyCode, modifiers, client);
                if (false == result) {
                  response["message"] = "failed to add key intercept";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::removeKeyInterceptWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            if (!parameters.HasLabel("keyCode"))
            {
                result = false;
                response["message"] = "please specify keyCode";
            }
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                //optional param?
                const JsonArray modifiers = parameters.HasLabel("modifiers") ? parameters["modifiers"].Array() : JsonArray();

                const uint32_t keyCode = parameters["keyCode"].Number();
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                result = removeKeyIntercept(keyCode, modifiers, client);
                if (false == result) {
                  response["message"] = "failed to remove key intercept";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::addKeyListenersWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            if (!parameters.HasLabel("keys"))
            {
                result = false;
                response["message"] = "please specify keys";
            }
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }

            if (result)
            {
                const JsonArray keys = parameters["keys"].Array();
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                result = addKeyListeners(client, keys);
                if (false == result) {
                  response["message"] = "failed to add key listeners";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::removeKeyListenersWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            if (!parameters.HasLabel("keys"))
            {
                result = false;
                response["message"] = "please specify keys";
            }
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }

            if (result)
            {
                const JsonArray keys = parameters["keys"].Array();
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                result = removeKeyListeners(client, keys);
                if (false == result) {
                  response["message"] = "failed to remove key listeners";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::addKeyMetadataListenerWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }

            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                gRdkShellMutex.lock();
                result = CompositorController::addKeyMetadataListener(client);
                gRdkShellMutex.unlock();
                if (false == result) {
                  response["message"] = "failed to add key metadata listeners";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::removeKeyMetadataListenerWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }

            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                gRdkShellMutex.lock();
                result = CompositorController::removeKeyMetadataListener(client);
                gRdkShellMutex.unlock();
                if (false == result) {
                  response["message"] = "failed to remove key metadata listeners";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::injectKeyWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            if (!parameters.HasLabel("keyCode"))
            {
                result = false;
                response["message"] = "please specify keyCode";
            }

            if (result)
            {
                //optional param?
                const JsonArray modifiers = parameters.HasLabel("modifiers") ? parameters["modifiers"].Array() : JsonArray();

                const uint32_t keyCode = parameters["keyCode"].Number();
                result = injectKey(keyCode, modifiers);
                if (false == result) {
                  response["message"] = "failed to inject key";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::generateKeyWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            if (!parameters.HasLabel("keys"))
            {
                result = false;
                response["message"] = "please specify keyInputs";
            }

            if (result)
            {
                const JsonArray keyInputs = parameters["keys"].Array();

                result = generateKey(keyInputs);
                if (false == result) {
                  response["message"] = "failed to generate keys";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::getScreenResolutionWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            UNUSED(parameters);

            bool result = true;
            if (!getScreenResolution(response))
            {
                response["message"] = "failed to get screen resolution";
                result = false;
            }
            returnResponse(result);
        }

        uint32_t RDKShell::setScreenResolutionWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("w"))
            {
                result = false;
                response["message"] = "please specify w";
            }
            if (!parameters.HasLabel("h"))
            {
                result = false;
                response["message"] = "please specify h";
            }
            if (result)
            {
                const unsigned int w  = parameters["w"].Number();
                const unsigned int h  = parameters["h"].Number();

                result = setScreenResolution(w, h);
                // Just realized: we need one more string& param for the the error message in case setScreenResolution() fails internally
                // Also, we might not need a "non-wrapper" method at all, nothing prevents us from implementing it right here
                if (false == result) {
                  response["message"] = "failed to set screen resolution";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::createDisplayWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                string displayName("");
                if (parameters.HasLabel("displayName"))
                {
                    displayName = parameters["displayName"].String();
                }
                result = createDisplay(client, displayName);
                if (false == result) {
                  response["message"] = "failed to create display";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::getClientsWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            UNUSED(parameters);
            bool result = true;
            JsonArray clients;
            if (!getClients(clients))
            {
                response["message"] = "failed to get clients";
                result = false;
            } else {
                response["clients"] = clients;
                result = true;
            }
            returnResponse(result);
        }

        uint32_t RDKShell::getZOrderWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            UNUSED(parameters);
            bool result = true;
            JsonArray clients;
            if (!getZOrder(clients))
            {
                response["message"] = "failed to get clients";
                result = false;
            } else {
                response["clients"] = clients;
                result = true;
            }
            returnResponse(result);
        }

        uint32_t RDKShell::getBoundsWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            UNUSED(parameters);
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result) {
              JsonObject bounds;
              string client;
              if (parameters.HasLabel("client"))
              {
                client = parameters["client"].String();
              }
              else
              {
                client = parameters["callsign"].String();
              }
              if (!getBounds(client, bounds))
              {
                  response["message"] = "failed to get bounds";
                  result = false;
              } else {
                  response["bounds"] = bounds;
                  result = true;
              }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::setBoundsWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }

                unsigned int x=0,y=0,w=0,h=0;
                gRdkShellMutex.lock();
                CompositorController::getBounds(client, x, y, w, h);
                gRdkShellMutex.unlock();
                if (parameters.HasLabel("x"))
                {
                    x  = parameters["x"].Number();
                }
                if (parameters.HasLabel("y"))
                {
                    y  = parameters["y"].Number();
                }
                if (parameters.HasLabel("w"))
                {
                    w  = parameters["w"].Number();
                }
                if (parameters.HasLabel("h"))
                {
                    h  = parameters["h"].Number();
                }

                result = setBounds(client, x, y, w, h);
                if (false == result) {
                  response["message"] = "failed to set bounds";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::getVisibilityWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                bool visible;
                result = getVisibility(client, visible);
                if (false == result) {
                  response["message"] = "failed to get visibility";
                }
                else {
                  response["visible"] = visible;
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::setVisibilityWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (!parameters.HasLabel("visible"))
            {
                result = false;
                response["message"] = "please specify visibility (visible = true/false)";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                const bool visible  = parameters["visible"].Boolean();

                result = setVisibility(client, visible);
                // Just realized: we need one more string& param for the the error message in case setScreenResolution() fails internally
                // Also, we might not need a "non-wrapper" method at all, nothing prevents us from implementing it right here

                if (false == result) {
                  response["message"] = "failed to set visibility";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::getOpacityWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            UNUSED(parameters);
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }

            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                unsigned int opacity;
                if (!getOpacity(client, opacity))
                {
                    response["message"] = "failed to get opacity";
                    result = false;
                } else {
                    response["opacity"] = opacity;
                    result = true;
                }
            }

            returnResponse(result);
        }

        uint32_t RDKShell::setOpacityWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (!parameters.HasLabel("opacity"))
            {
                result = false;
                response["message"] = "please specify opacity";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                const unsigned int  opacity  = parameters["opacity"].Number();

                result = setOpacity(client, opacity);
                if (false == result) {
                  response["message"] = "failed to set opacity";
                }
                // handle the result
            }
            returnResponse(result);
        }

        uint32_t RDKShell::getScaleWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            UNUSED(parameters);
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }

            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                double scaleX = 1.0;
                double scaleY = 1.0;
                if (!getScale(client, scaleX, scaleY))
                {
                    response["message"] = "failed to get scale";
                    result = false;
                } else {
                    response["sx"] = std::to_string(scaleX);
                    response["sy"] = std::to_string(scaleY);
                    result = true;
                }
            }

            returnResponse(result);
        }

        uint32_t RDKShell::setScaleWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (!parameters.HasLabel("sx") && !parameters.HasLabel("sy"))
            {
                result = false;
                response["message"] = "please specify sx and/or sy";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                double scaleX = 1.0;
                double scaleY = 1.0;
                getScale(client, scaleX, scaleY);
                if (parameters.HasLabel("sx"))
                {
                    scaleX = std::stod(parameters["sx"].String());
                }
                if (parameters.HasLabel("sy"))
                {
                    scaleY = std::stod(parameters["sy"].String());
                }

                result = setScale(client, scaleX, scaleY);
                if (false == result) {
                  response["message"] = "failed to set scale";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::getHolePunchWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                bool holePunch = true;
                result = getHolePunch(client, holePunch);
                if (false == result) {
                  response["message"] = "failed to get hole punch";
                }
                else {
                  response["holePunch"] = holePunch;
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::setHolePunchWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (!parameters.HasLabel("holePunch"))
            {
                result = false;
                response["message"] = "please specify hole punch (holePunch = true/false)";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                const bool holePunch  = parameters["holePunch"].Boolean();

                result = setHolePunch(client, holePunch);

                if (false == result) {
                  response["message"] = "failed to set hole punch";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::getLogLevelWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            std::string logLevel = "INFO";
            gRdkShellMutex.lock();
            result = CompositorController::getLogLevel(logLevel);
            gRdkShellMutex.unlock();
            if (false == result) {
                response["message"] = "failed to get log level";
            }
            else {
                response["logLevel"] = logLevel;
            }
            returnResponse(result);
        }

        uint32_t RDKShell::setLogLevelWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("logLevel"))
            {
                result = false;
                response["message"] = "please specify log level (logLevel = DEBUG/INFO/WARN/ERROR/FATAL)";
            }
            if (result)
            {
                std::string logLevel  = parameters["logLevel"].String();
                std::string currentLogLevel = "INFO";
                gRdkShellMutex.lock();
                result = CompositorController::setLogLevel(logLevel);
                CompositorController::getLogLevel(currentLogLevel);
                gRdkShellMutex.unlock();
                if (false == result) {
                    response["message"] = "failed to set log level";
                }
                else
                {
                    response["logLevel"] = currentLogLevel;
                }
            }
          returnResponse(result);
        }

        uint32_t RDKShell::hideSplashLogoWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            gRdkShellMutex.lock();
            result = CompositorController::hideSplashScreen();
            gRdkShellMutex.unlock();

            returnResponse(result);
        }

        uint32_t RDKShell::removeAnimationWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            UNUSED(parameters);
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }

            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }
                if (!removeAnimation(client))
                {
                    response["message"] = "failed to remove animation";
                    result = false;
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::addAnimationWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            if (parameters.HasLabel("animations"))
            {
                const JsonArray animations = parameters["animations"].Array();
                result = addAnimationList(animations);
                if (false == result) {
                    response["message"] = "failed to add animation list";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::enableInactivityReportingWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (false == mEnableUserInactivityNotification)
            {
                result = false;
                response["message"] = "feature is not enabled";
            }

            if (!parameters.HasLabel("enable"))
            {
                result = false;
                response["message"] = "please specify enable parameter";
            }
            if (result)
            {
                const bool enable  = parameters["enable"].Boolean();

                result = enableInactivityReporting(enable);

                if (false == result) {
                  response["message"] = "failed to set inactivity notification";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::setInactivityIntervalWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (false == mEnableUserInactivityNotification)
            {
                result = false;
                response["message"] = "feature is not enabled";
            }

            if (!parameters.HasLabel("interval"))
            {
                result = false;
                response["message"] = "please specify interval parameter";
            }
            if (result)
            {
                const unsigned int interval = parameters["interval"].Number();

                result = setInactivityInterval(interval);
                // Just realized: we need one more string& param for the the error message in case setScreenResolution() fails internally
                // Also, we might not need a "non-wrapper" method at all, nothing prevents us from implementing it right here

                if (false == result) {
                  response["message"] = "failed to set inactivity interval";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::scaleToFitWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client") && !parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                string client;
                if (parameters.HasLabel("client"))
                {
                    client = parameters["client"].String();
                }
                else
                {
                    client = parameters["callsign"].String();
                }

                unsigned int x = 0, y = 0;
                unsigned int clientWidth = 0, clientHeight = 0;
                gRdkShellMutex.lock();
                CompositorController::getBounds(client, x, y, clientWidth, clientHeight);
                if (parameters.HasLabel("x"))
                {
                    x = parameters["x"].Number();
                }
                if (parameters.HasLabel("y"))
                {
                    y = parameters["y"].Number();
                }
                if (parameters.HasLabel("w"))
                {
                    clientWidth = parameters["w"].Number();
                }
                if (parameters.HasLabel("h"))
                {
                    clientHeight = parameters["h"].Number();
                }
                result = CompositorController::scaleToFit(client, x, y, clientWidth, clientHeight);
                gRdkShellMutex.unlock();

                if (!result) {
                  response["message"] = "failed to scale to fit";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::launchWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            double launchStartTime = RdkShell::seconds();
            bool result = true;
            if (!parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify callsign";
            }

            if (result)
            {
                bool launchInProgress = false;
                int32_t currentLaunchCount = 0;
                gLaunchMutex.lock();
                if (gLaunchCount > 0)
                {
                    launchInProgress = true;
                }
                else
                {
                    gLaunchCount++;
                }
                currentLaunchCount = gLaunchCount;
                gLaunchMutex.unlock();
                std::cout << "the current launch count is " << currentLaunchCount << std::endl;
                if (launchInProgress)
                {
                    const string appCallsign = parameters["callsign"].String();
                    std::cout << "launch is in progress.  not able to launch another app: " << appCallsign << std::endl;
                    response["message"] = "failed to launch application.  another launch is in progress";
                    returnResponse(false);
                }
            }

            if (result)
            {
                RDKShellLaunchType launchType = RDKShellLaunchType::UNKNOWN;
                const string callsign = parameters["callsign"].String();
                const string callsignWithVersion = callsign + ".1";
                string type;
                string version = "0.0";
                string uri;
                int32_t x = 0;
                int32_t y = 0;
                uint32_t width = 0;
                uint32_t height = 0;
                bool suspend = false;
                bool visible = true;
                bool focused = true;
                string configuration;
                string behind;
                string displayName = "wst-" + callsign;
                bool scaleToFit = false;
                bool setSuspendResumeStateOnLaunch = true;
                bool holePunch = true;

                if (parameters.HasLabel("type"))
                {
                    type = parameters["type"].String();
                }
                if (parameters.HasLabel("version"))
                {
                    version = parameters["version"].String();
                }
                if (parameters.HasLabel("uri"))
                {
                    uri = parameters["uri"].String();
                }
                if (parameters.HasLabel("configuration"))
                {
                    configuration = parameters["configuration"].String();
                }
                if (parameters.HasLabel("behind"))
                {
                    behind = parameters["behind"].String();
                }
                if (parameters.HasLabel("displayName"))
                {
                    displayName = parameters["displayName"].String();
                }
                if (parameters.HasLabel("suspend"))
                {
                    suspend = parameters["suspend"].Boolean();
                }
                if (parameters.HasLabel("visible"))
                {
                    visible = parameters["visible"].Boolean();
                }
                if (parameters.HasLabel("focused"))
                {
                    focused = parameters["focused"].Boolean();
                }
                if (parameters.HasLabel("scaleToFit"))
                {
                    scaleToFit = parameters["scaleToFit"].Boolean();
                }
                if (parameters.HasLabel("w"))
                {
                    width = parameters["w"].Number();
                }
                if (parameters.HasLabel("h"))
                {
                    height = parameters["h"].Number();
                }
                if (parameters.HasLabel("holePunch"))
                {
                    holePunch = parameters["holePunch"].Boolean();
                }

                //check to see if plugin already exists
                bool newPluginFound = false;
                bool originalPluginFound = false;
                std::vector<std::string> foundTypes;
                for (auto pluginName : gActivePlugins)
                {
                  if (pluginName == callsign)
                  {
                    newPluginFound = true;
                    break;
                  }
                  else if (pluginName == type)
                  {
                    originalPluginFound = true;
                  }
                }
                auto thunderController = getThunderControllerClient();
                if ((false == newPluginFound) && (false == originalPluginFound))
                {
                    Core::JSON::ArrayType<PluginHost::MetaData::Service> availablePluginResult;
                    uint32_t status = thunderController->Get<Core::JSON::ArrayType<PluginHost::MetaData::Service>>(RDKSHELL_THUNDER_TIMEOUT, "status", availablePluginResult);

                    std::cout << "status status: " << status << std::endl;
                    if (status > 0)
                    {
                        std::cout << "trying status one more time...\n";
                        status = thunderController->Get<Core::JSON::ArrayType<PluginHost::MetaData::Service>>(RDKSHELL_THUNDER_TIMEOUT, "status", availablePluginResult);
                        std::cout << "status status: " << status << std::endl;
                    }

                    for (uint16_t i = 0; i < availablePluginResult.Length(); i++)
                    {
                        PluginHost::MetaData::Service service = availablePluginResult[i];
                        std::string pluginName = service.Callsign.Value();
                        pluginName.erase(std::remove(pluginName.begin(),pluginName.end(),'\"'),pluginName.end());
                        if (!pluginName.empty() && pluginName == callsign)
                        {
                            newPluginFound = true;
                            break;
                        }
                        else if (!pluginName.empty() && pluginName == type)
                        {
                            originalPluginFound = true;
                        }
                        foundTypes.push_back(pluginName);
                    }
                }

                if (!newPluginFound && !originalPluginFound)
                {
                    std::cout << "this type was not found: " << type << ".  unable to launch application.  list of types found: " << std::endl;
                    for (uint16_t i = 0; i < foundTypes.size(); i++)
                    {
                        std::cout << "available type " << i << ": " << foundTypes[i] << std::endl;
                    }
                    std::cout << "number of types found: " << foundTypes.size() << std::endl;
                    response["message"] = "failed to launch application.  type not found";
                    gLaunchMutex.lock();
                    gLaunchCount = 0;
                    gLaunchMutex.unlock();
                    std::cout << "new launch count loc1: 0\n";
                    returnResponse(false);
                }
                else if (!newPluginFound)
                {
                    std::cout << "attempting to clone type: " << type << " into " << callsign << std::endl;
                    JsonObject joParams;
                    joParams.Set("callsign", type);
                    joParams.Set("newcallsign",callsign.c_str());
                    JsonObject joResult;
                    // setting wait Time to 2 seconds
                    uint32_t status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, "clone", joParams, joResult);

                    std::cout << "clone status: " << status << std::endl;
                    if (status > 0)
                    {
                        std::cout << "trying status one more time...\n";
                        status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, "clone", joParams, joResult);
                        std::cout << "clone status: " << status << std::endl;
                    }

                    string strParams;
                    string strResult;
                    joParams.ToString(strParams);
                    joResult.ToString(strResult);
                    launchType = RDKShellLaunchType::CREATE;
                    RdkShell::CompositorController::createDisplay(callsign, displayName, width, height);
                }

                WPEFramework::Core::JSON::String configString;

                uint32_t status = 0;
                string method = "configuration@" + callsign;
                Core::JSON::ArrayType<PluginHost::MetaData::Service> joResult;
                status = thunderController->Get<WPEFramework::Core::JSON::String>(RDKSHELL_THUNDER_TIMEOUT, method.c_str(), configString);

                std::cout << "config status: " << status << std::endl;
                if (status > 0)
                {
                    std::cout << "trying status one more time...\n";
                    status = thunderController->Get<WPEFramework::Core::JSON::String>(RDKSHELL_THUNDER_TIMEOUT, method.c_str(), configString);
                    std::cout << "config status: " << status << std::endl;
                }

                JsonObject configSet;
                configSet.FromString(configString.Value());

                if (!configuration.empty())
                {
                    JsonObject configurationOverrides;
                    configurationOverrides.FromString(configuration);
                    JsonObject::Iterator configurationIterator = configurationOverrides.Variants();
                    while (configurationIterator.Next())
                    {
                        configSet[configurationIterator.Label()] = configurationIterator.Current();
                    }
                }
                configSet["clientidentifier"] = displayName;
                if (!newPluginFound && !type.empty() && type == "Netflix")
                {
                    std::cout << "setting launchtosuspend for Netflix: " << suspend << std::endl;
                    configSet["launchtosuspend"] = suspend;
                    if (!suspend)
                    {
                        setSuspendResumeStateOnLaunch = false;
                    }
                }

                status = thunderController->Set<JsonObject>(RDKSHELL_THUNDER_TIMEOUT, method.c_str(), configSet);

                std::cout << "set status: " << status << std::endl;
                if (status > 0)
                {
                    std::cout << "trying status one more time...\n";
                    status = thunderController->Set<JsonObject>(RDKSHELL_THUNDER_TIMEOUT, method.c_str(), configSet);
                    std::cout << "set status: " << status << std::endl;
                }

                if (launchType == RDKShellLaunchType::UNKNOWN)
                {
                    status = 0;
                    string statusMethod = "status@"+callsign;
                    Core::JSON::ArrayType<PluginHost::MetaData::Service> serviceResults;
                    status = thunderController->Get<Core::JSON::ArrayType<PluginHost::MetaData::Service> >(RDKSHELL_THUNDER_TIMEOUT, statusMethod.c_str(),serviceResults);

                    std::cout << "get status: " << status << std::endl;
                    if (status > 0)
                    {
                        std::cout << "trying status one more time...\n";
                        status = thunderController->Get<Core::JSON::ArrayType<PluginHost::MetaData::Service> >(RDKSHELL_THUNDER_TIMEOUT, statusMethod.c_str(),serviceResults);
                        std::cout << "get status: " << status << std::endl;
                    }

                    if (status == 0 && serviceResults.Length() > 0)
                    {
                        PluginHost::MetaData::Service service = serviceResults[0];
                        if (service.JSONState == PluginHost::MetaData::Service::state::DEACTIVATED ||
                            service.JSONState == PluginHost::MetaData::Service::state::DEACTIVATION ||
                            service.JSONState == PluginHost::MetaData::Service::state::PRECONDITION)
                        {
                            launchType = RDKShellLaunchType::ACTIVATE;
                            JsonObject activateParams;
                            activateParams.Set("callsign",callsign.c_str());
                            status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, "activate", activateParams, joResult);

                            std::cout << "activate 1 status: " << status << std::endl;
                            if (status > 0)
                            {
                                std::cout << "trying status one more time...\n";
                                status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, "activate", activateParams, joResult);
                                std::cout << "activate 1 status: " << status << std::endl;
                            }
                        }
                    }
                    else
                    {
                        launchType = RDKShellLaunchType::ACTIVATE;
                        JsonObject activateParams;
                        activateParams.Set("callsign",callsign.c_str());
                        status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, "activate", activateParams, joResult);
                        std::cout << "activate 2 status: " << status << std::endl;
                        if (status > 0)
                        {
                            std::cout << "trying status one more time...\n";
                            status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, "activate", activateParams, joResult);
                            std::cout << "activate 2 status: " << status << std::endl;
                        }
                    }
                }
                else
                {
                    JsonObject activateParams;
                    activateParams.Set("callsign",callsign.c_str());
                    status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, "activate", activateParams, joResult);

                    std::cout << "activate 3 status: " << status << std::endl;
                    if (status > 0)
                    {
                        std::cout << "trying status one more time...\n";
                        status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, "activate", activateParams, joResult);
                        std::cout << "activate 3 status: " << status << std::endl;
                    }
                }

                bool deferLaunch = false;
                if (status > 0)
                {
                    result = false;
                    std::cout << "error activating plugin.  status code is " << status << std::endl;
                }
                else
                {
                    uint32_t tempX = 0;
                    uint32_t tempY = 0;
                    uint32_t screenWidth = 0;
                    uint32_t screenHeight = 0;
                    gRdkShellMutex.lock();
                    CompositorController::getBounds(callsign, tempX, tempY, screenWidth, screenHeight);
                    gRdkShellMutex.unlock();
                    width = screenWidth;
                    height = screenHeight;
                    if (parameters.HasLabel("x"))
                    {
                        x = parameters["x"].Number();
                    }
                    if (parameters.HasLabel("y"))
                    {
                        y = parameters["y"].Number();
                    }
                    if (parameters.HasLabel("w"))
                    {
                        width = parameters["w"].Number();
                    }
                    if (parameters.HasLabel("h"))
                    {
                        height = parameters["h"].Number();
                    }
                    gRdkShellMutex.lock();
                    CompositorController::setBounds(callsign, x, y, width, height);
                    gRdkShellMutex.unlock();

                    if (scaleToFit)
                    {
                        std::cout << "scaling app to fit full screen" << std::endl;
                        double sx = 1.0;
                        double sy = 1.0;
                        if (width != screenWidth)
                        {
                            sx = (double)screenWidth / (double)width;
                        }
                        if (height != screenHeight)
                        {
                            sy = (double)screenHeight / (double)height;
                        }
                        setScale(callsign, sx, sy);
                    }

                    if (!behind.empty())
                    {
                        //check to ensure behind is a active client
                        std::cout << "moving " << callsign << " behind " << behind << std::endl;
                        bool moveBehindResult = moveBehind(callsign, behind);
                        if (!moveBehindResult)
                        {
                            std::cout << "unable to move behind " << behind << std::endl;
                        }
                    }

                    gPluginDataMutex.lock();
                    std::map<std::string, PluginStateChangeData*>::iterator pluginStateChangeEntry = gPluginsEventListener.find(callsign);
                    if (pluginStateChangeEntry == gPluginsEventListener.end())
                    {
                        std::shared_ptr<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement>> remoteObject = getThunderControllerClient(callsignWithVersion);
                        PluginStateChangeData* data = new PluginStateChangeData(callsign.c_str(), remoteObject, this);
                        gPluginsEventListener[callsign] = data;
                        remoteObject->Subscribe<JsonObject>(2000, _T("statechange"), &PluginStateChangeData::onStateChangeEvent, data);
                    }
                    else
                    {
                        PluginStateChangeData* data = pluginStateChangeEntry->second;    
                        data->enableLaunch(true);
                        deferLaunch = true;
                    }
                    gPluginDataMutex.unlock();
 
                    if (setSuspendResumeStateOnLaunch)
                    {
                        if (suspend)
                        {

                            WPEFramework::Core::JSON::String stateString;
                            stateString = "suspended";
                            status = getThunderControllerClient(callsignWithVersion)->Set<WPEFramework::Core::JSON::String>(RDKSHELL_THUNDER_TIMEOUT, "state", stateString);

                            std::cout << "setting the state to suspended\n";
                            if (launchType == RDKShellLaunchType::UNKNOWN)
                            {
                                launchType = RDKShellLaunchType::SUSPEND;
                            }
                            visible = false;
                        }
                        else
                        {
                            WPEFramework::Core::JSON::String stateString;
                            stateString = "resumed";
                            status = getThunderControllerClient(callsignWithVersion)->Set<WPEFramework::Core::JSON::String>(RDKSHELL_THUNDER_TIMEOUT, "state", stateString);
                            if (launchType == RDKShellLaunchType::UNKNOWN)
                            {
                                launchType = RDKShellLaunchType::RESUME;
                            }

                            std::cout << "setting the state to resumed\n";
                        }
                    }
                    setVisibility(callsign, visible);
                    setHolePunch(callsign, holePunch);
                    if (!visible)
                    {
                        focused = false;
                    }
                    if (focused)
                    {
                        std::cout << "setting the focused app to " << callsign << std::endl;
                        setFocus(callsign);
                    }

                    JsonObject urlResult;
                    if (!uri.empty())
                    {
                        WPEFramework::Core::JSON::String urlString;
                        urlString = uri;
                        status = getThunderControllerClient(callsignWithVersion)->Set<WPEFramework::Core::JSON::String>(RDKSHELL_THUNDER_TIMEOUT, "url",urlString);
                        if (status > 0)
                        {
                            std::cout << "failed to set url to " << uri << " with status code " << status << std::endl;
                        }
                    }
                }

                if (status > 0 || !result)
                {
                    result = false;
                }
                else
                {
                    string launchTypeString;
                    switch (launchType)
                    {
                        case CREATE:
                            launchTypeString = "create";
                            break;
                        case ACTIVATE:
                            launchTypeString = "activate";
                            break;
                        case SUSPEND:
                            launchTypeString = "suspend";
                            break;
                        case RESUME:
                            launchTypeString = "resume";
                            break;
                        default:
                            launchTypeString = "unknown";
                            break;
                    }
                    std::cout << "Application:" << callsign << " took " << (RdkShell::seconds() - launchStartTime)*1000 << " milliseconds to launch " << std::endl;
                    gLaunchMutex.lock();
                    gLaunchCount = 0;
                    gLaunchMutex.unlock();
                    if (setSuspendResumeStateOnLaunch && deferLaunch && ((launchType == SUSPEND) || (launchType == RESUME)))
                    {
                        std::cout << "deferring application launch " << std::endl;
                    }
                    else
                    {
                        onLaunched(callsign, launchTypeString);
                    }
                    response["launchType"] = launchTypeString;
                }
                
            }
            if (!result) 
            {
                response["message"] = "failed to launch application";
            }
            gLaunchMutex.lock();
            gLaunchCount = 0;
            gLaunchMutex.unlock();
            std::cout << "new launch count at loc2 is 0\n";

            returnResponse(result);
        }

        uint32_t RDKShell::suspendWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify callsign";
            }
            if (result)
            {
                const string callsign = parameters["callsign"].String();
                std::cout << "about to suspend " << callsign << std::endl;

                WPEFramework::Core::JSON::String stateString;
                stateString = "suspended";
                const string callsignWithVersion = callsign + ".1";
                uint32_t status = getThunderControllerClient(callsignWithVersion)->Set<WPEFramework::Core::JSON::String>(RDKSHELL_THUNDER_TIMEOUT, "state", stateString);

                if (status > 0)
                {
                    std::cout << "failed to suspend " << callsign << ".  status: " << status << std::endl;
                    result = false;
                }
                else
                {
                    setVisibility(callsign, false);
                    onSuspended(callsign);
                }
            }
            if (!result)
            {
                response["message"] = "failed to suspend application";
            }
            returnResponse(result);
        }

        uint32_t RDKShell::destroyWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("callsign"))
            {
                result = false;
                response["message"] = "please specify callsign";
            }
            if (result)
            {
                const string callsign = parameters["callsign"].String();
                std::cout << "destroying " << callsign << std::endl;
                JsonObject joParams;
                joParams.Set("callsign",callsign.c_str());
                JsonObject joResult;
                auto thunderController = getThunderControllerClient();
                uint32_t status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, "deactivate", joParams, joResult);
                if (status > 0)
                {
                    std::cout << "failed to destroy " << callsign << ".  status: " << status << std::endl;
                    result = false;
                }
                else
                {
                    onDestroyed(callsign);
                }
            }
            if (!result)
            {
                response["message"] = "failed to destroy application";
            }
            returnResponse(result);
        }

        uint32_t RDKShell::launchApplicationWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (!parameters.HasLabel("uri"))
            {
                result = false;
                response["message"] = "please specify uri";
            }
            if (!parameters.HasLabel("mimeType"))
            {
                result = false;
                response["message"] = "please specify mimeType";
            }
            if (result)
            {
                const string client = parameters["client"].String();
                const string uri = parameters["uri"].String();
                const string mimeType = parameters["mimeType"].String();

                if (mimeType == RDKSHELL_APPLICATION_MIME_TYPE_DAC_NATIVE)
                {
                    // Starting a DAC app. Get the info from Packager
                    LOGINFO("Starting DAC app");

                    auto packagerPlugin = getPackagerPlugin();
                    if (!packagerPlugin)
                    {
                        response["message"] = "Packager initialisation failed";
                        returnResponse(false);
                    }

                    // See if the app is actually installed
                    JsonObject installParams;
                    JsonObject installResult;

                    installParams.Set("pkgId", uri.c_str());
                    packagerPlugin->Invoke<JsonObject, JsonObject>(1000, "isInstalled", installParams, installResult);

                    if (!installResult.Get("available").Boolean())
                    {
                        response["message"] = "Packager reports app is not installed";
                        returnResponse(false);
                    }

                    // App is installed, find the bundle location
                    JsonObject infoParams;
                    JsonObject infoResult;

                    infoParams.Set("pkgId", uri.c_str());
                    packagerPlugin->Invoke<JsonObject, JsonObject>(1000, "getPackageInfo", infoParams, infoResult);

                    string bundlePath = infoResult["bundlePath"].String();

                    // We know where the app lives and are ready to start it,
                    // create a display with rdkshell
                    if (!createDisplay(client, uri))
                    {
                        response["message"] = "Could not create display";
                        returnResponse(false);
                    }

                    string runtimeDir = getenv("XDG_RUNTIME_DIR");
                    string display = runtimeDir + "/" + uri;

                    // Set mime type
                    if (!setMimeType(client, mimeType))
                    {
                        LOGWARN("Failed to set mime type - non fatal...");
                    }

                    // Start container
                    auto ociContainerPlugin = getOCIContainerPlugin();
                    if (!ociContainerPlugin)
                    {
                        response["message"] = "OCIContainer initialisation failed";
                        returnResponse(false);
                    }

                    JsonObject ociContainerResult;
                    JsonObject param;

                    // Container ID set to client so we can find the container
                    // when suspend/resume/killing which use client id
                    param["containerId"] = client;
                    param["bundlePath"] = bundlePath;
                    param["westerosSocket"] = display;

                    ociContainerPlugin->Invoke<JsonObject, JsonObject>(RDKSHELL_THUNDER_TIMEOUT, "startContainer", param, ociContainerResult);

                    if (!ociContainerResult["success"].Boolean())
                    {
                        // Something went wrong starting the container, destory the display we just created
                        kill(client);
                        response["message"] = "Could not start Dobby container";
                        returnResponse(false);
                    }
                }
                else if (mimeType == RDKSHELL_APPLICATION_MIME_TYPE_NATIVE)
                {
                    gRdkShellMutex.lock();
                    result = CompositorController::launchApplication(client, uri, mimeType);
                    gRdkShellMutex.unlock();

                    if (!result)
                    {
                        response["message"] = "failed to launch application";
                    }
                }
                else
                {
                    result = false;
                    response["message"] = "Unsupported MIME type";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::suspendApplicationWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                const string client = parameters["client"].String();

                std::string mimeType;
                if (!getMimeType(client, mimeType))
                {
                    response["message"] = "Could not determine app mime type";
                    returnResponse(false);
                }

                if (mimeType == RDKSHELL_APPLICATION_MIME_TYPE_NATIVE)
                {
                    gRdkShellMutex.lock();
                    result = CompositorController::suspendApplication(client);
                    gRdkShellMutex.unlock();
                }
                else if (mimeType == RDKSHELL_APPLICATION_MIME_TYPE_DAC_NATIVE)
                {
                    // Pause the container with Dobby
                    LOGINFO("Pausing DAC app");

                    auto ociContainerPlugin = getOCIContainerPlugin();

                    if (!ociContainerPlugin)
                    {
                        response["message"] = "OCIContainer initialisation failed";
                        returnResponse(false);
                    }

                    JsonObject ociContainerResult;
                    JsonObject param;
                    param["containerId"] = client;

                    ociContainerPlugin->Invoke<JsonObject, JsonObject>(RDKSHELL_THUNDER_TIMEOUT, "pauseContainer", param, ociContainerResult);

                    if (!ociContainerResult["success"].Boolean())
                    {
                        response["message"] = "Could not pause container";
                        returnResponse(false);
                    }
                }
                else
                {
                    response["message"] = "Unsupported mime type";
                    returnResponse(false);
                }

                // Make the application hidden
                result = setVisibility(client, false);
                if (!result)
                {
                    response["message"] = "failed to suspend application";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::resumeApplicationWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("client"))
            {
                result = false;
                response["message"] = "please specify client";
            }
            if (result)
            {
                const string client = parameters["client"].String();

                std::string mimeType;
                if (!getMimeType(client, mimeType))
                {
                    response["message"] = "Could not determine app mime type";
                    returnResponse(false);
                }

                if (mimeType == RDKSHELL_APPLICATION_MIME_TYPE_NATIVE)
                {
                    gRdkShellMutex.lock();
                    result = CompositorController::resumeApplication(client);
                    gRdkShellMutex.unlock();
                }
                else if (mimeType == RDKSHELL_APPLICATION_MIME_TYPE_DAC_NATIVE)
                {
                    // Resume the container with Dobby
                    LOGINFO("Resuming DAC app");

                    auto ociContainerPlugin = getOCIContainerPlugin();
                    if (!ociContainerPlugin)
                    {
                        response["message"] = "OCIContainer initialisation failed";
                        returnResponse(false);
                    }

                    JsonObject ociContainerResult;
                    JsonObject param;

                    param["containerId"] = client;
                    ociContainerPlugin->Invoke<JsonObject, JsonObject>(RDKSHELL_THUNDER_TIMEOUT, "resumeContainer", param, ociContainerResult);

                    if (!ociContainerResult["success"].Boolean())
                    {
                        response["message"] = "Could not resume container";
                        returnResponse(false);
                    }
                }
                else
                {
                    response["message"] = "Unsupported mime type";
                    returnResponse(false);
                }

                // Make the application visible
                result = setVisibility(client, true);

                if (!result)
                {
                    response["message"] = "failed to resume application";
                }
            }
            returnResponse(result);
        }

        uint32_t RDKShell::getAvailableTypesWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            string method = "status";
            Core::JSON::ArrayType<PluginHost::MetaData::Service> joResult;
            auto thunderController = getThunderControllerClient();
            uint32_t status = thunderController->Get<Core::JSON::ArrayType<PluginHost::MetaData::Service>>(RDKSHELL_THUNDER_TIMEOUT, method.c_str(), joResult);

            JsonArray availableTypes;
            for (uint16_t i = 0; i < joResult.Length(); i++)
            {
                PluginHost::MetaData::Service service = joResult[i];
                std::string configLine;
                service.Configuration.ToString(configLine);
                if (!configLine.empty())
                {
                    JsonObject serviceConfig = JsonObject(configLine.c_str());
                    if (serviceConfig.HasLabel("clientidentifier"))
                    {
                        std::string typeName;
                        service.Callsign.ToString(typeName);
                        typeName.erase(std::remove(typeName.begin(),typeName.end(),'\"'),typeName.end());
                        availableTypes.Add(typeName);
                    }
                }
            }
            response["types"] = availableTypes;

            returnResponse(result);
        }

        uint32_t RDKShell::getState(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            string method = "status";
            Core::JSON::ArrayType<PluginHost::MetaData::Service> joResult;
            auto thunderController = getThunderControllerClient();
            uint32_t status = thunderController->Get<Core::JSON::ArrayType<PluginHost::MetaData::Service>>(RDKSHELL_THUNDER_TIMEOUT, method.c_str(), joResult);


            JsonArray stateArray;
            for (uint16_t i = 0; i < joResult.Length(); i++)
            {
                PluginHost::MetaData::Service service = joResult[i];
                if (service.JSONState != PluginHost::MetaData::Service::state::DEACTIVATED &&
                    service.JSONState != PluginHost::MetaData::Service::state::DEACTIVATION &&
                    service.JSONState != PluginHost::MetaData::Service::state::PRECONDITION)
                {
                    std::string configLine;
                    service.Configuration.ToString(configLine);
                    if (!configLine.empty())
                    {
                        JsonObject serviceConfig = JsonObject(configLine.c_str());
                        if (serviceConfig.HasLabel("clientidentifier"))
                        {
                            std::string callsign;
                            service.Callsign.ToString(callsign);
                            callsign.erase(std::remove(callsign.begin(),callsign.end(),'\"'),callsign.end());

                            WPEFramework::Core::JSON::String stateString;
                            const string callsignWithVersion = callsign + ".1";
                            auto thunderPlugin = getThunderControllerClient(callsignWithVersion);
                            uint32_t stateStatus = thunderPlugin->Get<WPEFramework::Core::JSON::String>(RDKSHELL_THUNDER_TIMEOUT, "state", stateString);

                            if (stateStatus == 0)
                            {
                                WPEFramework::Core::JSON::String urlString;
                                uint32_t urlStatus = thunderPlugin->Get<WPEFramework::Core::JSON::String>(RDKSHELL_THUNDER_TIMEOUT, "url",urlString);

                                JsonObject typeObject;
                                typeObject["callsign"] = callsign;
                                typeObject["state"] = stateString.Value();
                                if (urlStatus == 0)
                                {
                                    typeObject["uri"] = urlString.Value();
                                }
                                else
                                {
                                    typeObject["uri"] = "";
                                }
                                stateArray.Add(typeObject);
                            }
                        }
                    }
                }
            }
            response["state"] = stateArray;

            returnResponse(result);
        }

        uint32_t RDKShell::getSystemMemoryWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            uint32_t freeKb=0, usedSwapKb=0, totalKb=0;
            result = systemMemory(freeKb, totalKb, usedSwapKb);
            if (!result) {
              response["message"] = "failed to get system Ram";
            }
            else
            {
              response["freeRam"] = freeKb;
              response["swapRam"] = usedSwapKb;
              response["totalRam"] = totalKb;
            }
            returnResponse(result);
        }

        uint32_t RDKShell::getSystemResourceInfoWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;

            JsonArray memoryInfo;

            string method = "status";
            Core::JSON::ArrayType<PluginHost::MetaData::Service> joResult;
            auto thunderController = getThunderControllerClient();
            uint32_t status = thunderController->Get<Core::JSON::ArrayType<PluginHost::MetaData::Service>>(RDKSHELL_THUNDER_TIMEOUT, method.c_str(), joResult);

            /*std::cout << "DEACTIVATED: " << PluginHost::MetaData::Service::state::DEACTIVATED << std::endl;
                    std::cout << "DEACTIVATION: " << PluginHost::MetaData::Service::state::DEACTIVATION << std::endl;
                    std::cout << "ACTIVATED: " << PluginHost::MetaData::Service::state::ACTIVATED << std::endl;
                    std::cout << "ACTIVATION: " << PluginHost::MetaData::Service::state::ACTIVATION << std::endl;
                    std::cout << "DESTROYED: " << PluginHost::MetaData::Service::state::DESTROYED << std::endl;
                    std::cout << "PRECONDITION: " << PluginHost::MetaData::Service::state::PRECONDITION << std::endl;
                    std::cout << "SUSPENDED: " << PluginHost::MetaData::Service::state::SUSPENDED << std::endl;
                    std::cout << "RESUMED: " << PluginHost::MetaData::Service::state::RESUMED << std::endl;*/

            JsonArray stateArray;
            for (uint16_t i = 0; i < joResult.Length(); i++)
            {
                PluginHost::MetaData::Service service = joResult[i];
                if (service.JSONState != PluginHost::MetaData::Service::state::DEACTIVATED &&
                    service.JSONState != PluginHost::MetaData::Service::state::DEACTIVATION &&
                    service.JSONState != PluginHost::MetaData::Service::state::PRECONDITION)
                {
                    std::string configLine;
                    service.Configuration.ToString(configLine);
                    if (!configLine.empty())
                    {
                        JsonObject serviceConfig = JsonObject(configLine.c_str());
                        if (serviceConfig.HasLabel("clientidentifier"))
                        {
                            std::string callsign;
                            service.Callsign.ToString(callsign);
                            callsign.erase(std::remove(callsign.begin(),callsign.end(),'\"'),callsign.end());

                            WPEFramework::Core::JSON::String stateString;
                            const string callsignWithVersion = callsign + ".1";
                            uint32_t stateStatus = getThunderControllerClient(callsignWithVersion)->Get<WPEFramework::Core::JSON::String>(RDKSHELL_THUNDER_TIMEOUT, "state", stateString);

                            if (stateStatus == 0)
                            {
                                result = pluginMemoryUsage(callsign, memoryInfo);
                            }
                        }
                    }
                }
            }

            response["types"] = memoryInfo;

            returnResponse(result);
        }

        uint32_t RDKShell::setMemoryMonitorWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            bool result = true;
            if (!parameters.HasLabel("enable"))
            {
                result = false;
                response["message"] = "please specify enable parameter";
            }
            if (result)
            {
              std::map<std::string, RdkShellData> configuration;
              configuration["enable"] = parameters["enable"].Boolean();
            
              if (parameters.HasLabel("interval"))
              {
                configuration["interval"] = std::stod(parameters["interval"].String());
              }
              if (parameters.HasLabel("lowRam"))
              {
                configuration["lowRam"] = std::stod(parameters["lowRam"].String());
              }
              if (parameters.HasLabel("criticallyLowRam"))
              {
                configuration["criticallyLowRam"] = std::stod(parameters["criticallyLowRam"].String());
              }
              RdkShell::setMemoryMonitor(configuration);
            }
            returnResponse(result);
        }

        uint32_t RDKShell::launchFactoryAppWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            if (!gSystemServiceEventsSubscribed && (nullptr != gSystemServiceConnection))
            {
                std::string eventName("onSystemPowerStateChanged");
                int32_t status = gSystemServiceConnection->Subscribe<JsonObject>(RDKSHELL_THUNDER_TIMEOUT, _T(eventName), &RDKShell::pluginEventHandler, this);
                if (status == 0)
                {
                    std::cout << "RDKShell subscribed to onSystemPowerStateChanged event " << std::endl;
                    gSystemServiceEventsSubscribed = true;
                }
            }
            if (parameters.HasLabel("startup"))
            {
                bool startup = parameters["startup"].Boolean();
                if (startup)
                {
                    JsonObject joAgingParams;
                    JsonObject joAgingResult;
                    joAgingParams.Set("namespace","FactoryTest");
                    joAgingParams.Set("key","AgingState");
                    std::string agingGetInvoke = "org.rdk.PersistentStore.1.getValue";

                    std::cout << "attempting to check aging flag \n";
                    uint32_t status = getThunderControllerClient()->Invoke(RDKSHELL_THUNDER_TIMEOUT, agingGetInvoke.c_str(), joAgingParams, joAgingResult);
                    std::cout << "get status: " << status << std::endl;

                    if (status > 0)
                    {
                        response["message"] = " unable to check aging flag";
                        returnResponse(false);
                    }

                    if (!joAgingResult.HasLabel("value"))
                    {
                        response["message"] = " aging value not found";
                        returnResponse(false);
                    }

                    const std::string valueString = joAgingResult["value"].String();
                    if (valueString != "true")
                    {
                        std::cout << "aging value is " << valueString << std::endl;
                        response["message"] = " aging is not set for startup";
                        returnResponse(false);
                    }
                }
            }

            uint32_t result;
            killAllApps();
            JsonObject destroyRequest, destroyResponse;
            destroyRequest["callsign"] = "ResidentApp";
            result = destroyWrapper(destroyRequest, destroyResponse);
            char* factoryAppUrl = getenv("RDKSHELL_FACTORY_APP_URL");
            if (NULL != factoryAppUrl)
            {
                JsonObject launchRequest;
                launchRequest["callsign"] = "factoryapp";
                launchRequest["type"] = "ResidentApp";
                launchRequest["uri"] = std::string(factoryAppUrl);
                launchRequest["focused"] = true;
                std::cout << "launching " << launchRequest["callsign"].String().c_str() << std::endl;
                result = launchWrapper(launchRequest, response);
                bool launchFactoryResult = response.HasLabel("success")?response["success"].Boolean():false;
                if (true == launchFactoryResult)
                {
                    std::cout << "Launching factory application succeeded " << std::endl;
                }
                else
                {
                    std::cout << "Launching factory application failed " << std::endl;
                    response["message"] = " launching factory application failed ";
                    returnResponse(false);
                }
                JsonObject joFactoryModeParams;
                JsonObject joFactoryModeResult;
                joFactoryModeParams.Set("namespace","FactoryTest");
                joFactoryModeParams.Set("key","FactoryMode");
                joFactoryModeParams.Set("value","true");
                std::string factoryModeSetInvoke = "org.rdk.PersistentStore.1.setValue";

                std::cout << "attempting to set factory mode flag \n";
                uint32_t setStatus = getThunderControllerClient()->Invoke(RDKSHELL_THUNDER_TIMEOUT, factoryModeSetInvoke.c_str(), joFactoryModeParams, joFactoryModeResult);
                std::cout << "set status: " << setStatus << std::endl;
                returnResponse(true);
            }
            else
            {
                std::cout << "factory app url is empty " << std::endl;
                response["message"] = " factory app url is empty";
                returnResponse(false);
            }
        }

        uint32_t RDKShell::launchFactoryAppShortcutWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            
            JsonObject joToFacParams;
            JsonObject joToFacResult;
            joToFacParams.Set("namespace","FactoryTest");
            joToFacParams.Set("key","ToFacFlag");
            std::string toFacGetInvoke = "org.rdk.PersistentStore.1.getValue";

            std::cout << "attempting to check flag \n";
            auto thunderController = getThunderControllerClient();
            uint32_t status = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, toFacGetInvoke.c_str(), joToFacParams, joToFacResult);
            std::cout << "get status: " << status << std::endl;

            if (status > 0)
            {
                response["message"] = " unable to check toFac flag";
                returnResponse(false);
            }

            if (!joToFacResult.HasLabel("value"))
            {
                response["message"] = " toFac value not found";
                returnResponse(false);
            }

            const std::string valueString = joToFacResult["value"].String();
            if (valueString != "M" && valueString != "m")
            {
                std::cout << "toFac value is " << valueString << std::endl;
                response["message"] = " toFac not in the correct mode";
                returnResponse(false);
            }

            std::string callsign("factoryapp");
            bool isFactoryAppRunning = false;
            gPluginDataMutex.lock();
            for (auto pluginName : gActivePlugins)
            {
                if (pluginName == callsign)
                {
                    std::cout << "factory app is already running" << std::endl;
                    isFactoryAppRunning = true;
                    break;
                }
            }
            gPluginDataMutex.unlock();
            if (isFactoryAppRunning)
            {
                std::cout << "factory app is arleady running, do nothing";
                response["message"] = " factory mode already running";
                returnResponse(false);
            }

            return launchFactoryAppWrapper(parameters, response);
        }

        uint32_t RDKShell::launchResidentAppWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            std::string factoryAppCallsign("factoryapp");
            bool isFactoryAppRunning = false;
            gPluginDataMutex.lock();
            for (auto pluginName : gActivePlugins)
            {
                if (pluginName == factoryAppCallsign)
                {
                    std::cout << "factory app is running" << std::endl;
                    isFactoryAppRunning = true;
                    break;
                }
            }
            gPluginDataMutex.unlock();
            if (!isFactoryAppRunning)
            {
                std::cout << "nothing to do since factory app is not running\n";
                returnResponse(true);
            }
            else
            {
                JsonObject joAgingParams;
                JsonObject joAgingResult;
                joAgingParams.Set("namespace","FactoryTest");
                joAgingParams.Set("key","AgingState");
                std::string agingGetInvoke = "org.rdk.PersistentStore.1.getValue";

                std::cout << "attempting to check aging flag \n";
                uint32_t agingStatus = getThunderControllerClient()->Invoke(RDKSHELL_THUNDER_TIMEOUT, agingGetInvoke.c_str(), joAgingParams, joAgingResult);
                std::cout << "aging get status: " << agingStatus << std::endl;

                if (agingStatus == 0 && joAgingResult.HasLabel("value"))
                {
                    const std::string valueString = joAgingResult["value"].String();
                    std::cout << "aging value is " << valueString << std::endl;
                    if (valueString == "true")
                    {
                        std::cout << "do not exit the factory app\n";
                        response["message"] = " aging is true, do not exit the factory app";
                        returnResponse(false);
                    }
                }
                else
                {
                    std::cout << "aging value is not set\n";
                }
            }
            killAllApps();
            //try to kill factoryapp once more if kill apps missed killing due to timeout
            JsonObject destroyRequest, destroyResponse;
            destroyRequest["callsign"] = "factoryapp";
            uint32_t result = destroyWrapper(destroyRequest, destroyResponse);

            std::cout << "attempting to stop hdmi input...\n";
            JsonObject joStopHdmiParams;
            JsonObject joStopHdmiResult;
            std::string stopHdmiInvoke = "org.rdk.HdmiInput.1.stopHdmiInput";

            std::cout << "attempting to stop hdmi input \n";
            uint32_t stopHdmiStatus = getThunderControllerClient()->Invoke(RDKSHELL_THUNDER_TIMEOUT, stopHdmiInvoke.c_str(), joStopHdmiParams, joStopHdmiResult);
            std::cout << "stopHdmiStatus status: " << stopHdmiStatus << std::endl;

            bool ret = true;
            std::string callsign("ResidentApp");
            JsonObject activateParams;
            activateParams.Set("callsign",callsign.c_str());
            JsonObject activateResult;
            auto thunderController = getThunderControllerClient();
            int32_t status = thunderController->Invoke(3500, "activate", activateParams, activateResult);

            std::cout << "activate resident app status: " << status << std::endl;
            if (status > 0)
            {
                std::cout << "trying status one more time...\n";
                status = thunderController->Invoke(3500, "activate", activateParams, activateResult);
                std::cout << "activate resident app status: " << status << std::endl;
                if (status > 0)
                {
                    response["message"] = "resident app launch failed";
                    ret = false;
                }
                else
                {
                    ret = true;
                }
            }
            JsonObject joFactoryModeParams;
            JsonObject joFactoryModeResult;
            joFactoryModeParams.Set("namespace","FactoryTest");
            joFactoryModeParams.Set("key","FactoryMode");
            joFactoryModeParams.Set("value","false");
            std::string factoryModeSetInvoke = "org.rdk.PersistentStore.1.setValue";

            std::cout << "attempting to set factory mode flag \n";
            uint32_t setStatus = thunderController->Invoke(RDKSHELL_THUNDER_TIMEOUT, factoryModeSetInvoke.c_str(), joFactoryModeParams, joFactoryModeResult);
            std::cout << "set status: " << setStatus << std::endl;
            returnResponse(ret);
        }

        uint32_t RDKShell::toggleFactoryAppWrapper(const JsonObject& parameters, JsonObject& response)
        {
            LOGINFOMETHOD();
            std::string callsign("factoryapp");
            bool isFactoryAppRunning = false;
            gPluginDataMutex.lock();
            for (auto pluginName : gActivePlugins)
            {
                if (pluginName == callsign)
                {
                    std::cout << "factory app is already running" << std::endl;
                    isFactoryAppRunning = true;
                    break;
                }
            }
            gPluginDataMutex.unlock();
            if (isFactoryAppRunning)
            {
                launchResidentAppWrapper(parameters, response);
            }
            else
            {
                launchFactoryAppWrapper(parameters, response);
            }
        }
        // Registered methods begin

        // Events begin
        void RDKShell::notify(const std::string& event, const JsonObject& parameters)
        {
            sendNotify(event.c_str(), parameters);
        }
      // Events end

        void RDKShell::killAllApps()
        {
            bool ret = false;
            JsonObject stateRequest, stateResponse;
            uint32_t result = getState(stateRequest, stateResponse);
            const JsonArray stateList = stateResponse.HasLabel("state")?stateResponse["state"].Array():JsonArray();
            for (int i=0; i<stateList.Length(); i++)
            {
                const JsonObject& stateInfo = stateList[i].Object();
                if (stateInfo.HasLabel("callsign"))
                {
                   JsonObject destroyRequest, destroyResponse;
                   destroyRequest["callsign"] = stateInfo["callsign"].String();
                   result = destroyWrapper(destroyRequest, destroyResponse);
                }
            }
        }

        // Internal methods begin
        bool RDKShell::moveToFront(const string& client)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::moveToFront(client);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::moveToBack(const string& client)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::moveToBack(client);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::moveBehind(const string& client, const string& target)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            std::vector<std::string> clientList;
            CompositorController::getClients(clientList);
            bool targetFound = false;
            for (size_t i=0; i<clientList.size(); i++)
            {
                if (strcasecmp(clientList[i].c_str(),target.c_str()) == 0)
                {
                    targetFound = true;
                    break;
                }
            }
            if (targetFound)
            {
                ret = CompositorController::moveBehind(client, target);
            }
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::setFocus(const string& client)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::setFocus(client);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::kill(const string& client)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            RdkShell::CompositorController::removeListener(client, mEventListener);
            ret = CompositorController::kill(client);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::addKeyIntercept(const uint32_t& keyCode, const JsonArray& modifiers, const string& client)
        {
            uint32_t flags = 0;
            for (int i=0; i<modifiers.Length(); i++) {
              flags |= getKeyFlag(modifiers[i].String());
            }
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::addKeyIntercept(client, keyCode, flags);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::removeKeyIntercept(const uint32_t& keyCode, const JsonArray& modifiers, const string& client)
        {
            uint32_t flags = 0;
            for (int i=0; i<modifiers.Length(); i++) {
              flags |= getKeyFlag(modifiers[i].String());
            }
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::removeKeyIntercept(client, keyCode, flags);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::addKeyListeners(const string& client, const JsonArray& keys)
        {
            gRdkShellMutex.lock();

            bool result = true;

            for (int i=0; i<keys.Length(); i++) {

                result = false;
                const JsonObject& keyInfo = keys[i].Object();

                if (keyInfo.HasLabel("keyCode") && keyInfo.HasLabel("nativeKeyCode"))
                {
                    std::cout << "ERROR: keyCode and nativeKeyCode can't be set both at the same time" << std::endl;
                }
                else if (keyInfo.HasLabel("keyCode") || keyInfo.HasLabel("nativeKeyCode"))
                {
                    uint32_t keyCode = 0;

                    if (keyInfo.HasLabel("keyCode"))
                    {
                        std::string keystring = keyInfo["keyCode"].String();
                        if (keystring.compare("*") == 0)
                        {
                          keyCode = ANY_KEY;
                        }
                        else
                        {
                          keyCode = keyInfo["keyCode"].Number();
                        }
                    }
                    else
                    {
                        std::string keystring = keyInfo["nativeKeyCode"].String();
                        if (keystring.compare("*") == 0)
                        {
                            keyCode = ANY_KEY;
                        }
                        else
                        {
                            keyCode = keyInfo["nativeKeyCode"].Number();
                        }
                    }
                    const JsonArray modifiers = keyInfo.HasLabel("modifiers") ? keyInfo["modifiers"].Array() : JsonArray();
                    uint32_t flags = 0;
                    for (int i=0; i<modifiers.Length(); i++) {
                      flags |= getKeyFlag(modifiers[i].String());
                    }
                    std::map<std::string, RdkShellData> properties;
                    if (keyInfo.HasLabel("activate"))
                    {
                        bool activate = keyInfo["activate"].Boolean();
                        properties["activate"] = activate;
                    }
                    if (keyInfo.HasLabel("propagate"))
                    {
                        bool propagate = keyInfo["propagate"].Boolean();
                        properties["propagate"] = propagate;
                    }

                    if (keyInfo.HasLabel("keyCode"))
                    {
                        result = CompositorController::addKeyListener(client, keyCode, flags, properties);
                    }
                    else
                    {
                        result = CompositorController::addNativeKeyListener(client, keyCode, flags, properties);
                    }
                }
                else
                {
                    std::cout << "ERROR: Neither keyCode nor nativeKeyCode provided" << std::endl;
                }

                if (result == false)
                {
                    break;
                }
            }
            gRdkShellMutex.unlock();
            return result;
        }

        bool RDKShell::removeKeyListeners(const string& client, const JsonArray& keys)
        {
            gRdkShellMutex.lock();

            bool result = true;

            for (int i=0; i<keys.Length(); i++) {

                result = false;
                const JsonObject& keyInfo = keys[i].Object();

                if (keyInfo.HasLabel("keyCode") && keyInfo.HasLabel("nativeKeyCode"))
                {
                    std::cout << "ERROR: keyCode and nativeKeyCode can't be set both at the same time" << std::endl;
                }
                else if (keyInfo.HasLabel("keyCode") || keyInfo.HasLabel("nativeKeyCode"))
                {
                    uint32_t keyCode = 0;
                    if (keyInfo.HasLabel("keyCode"))
                    {
                        std::string keystring = keyInfo["keyCode"].String();
                        if (keystring.compare("*") == 0)
                        {
                          keyCode = ANY_KEY;
                        }
                        else
                        {
                          keyCode = keyInfo["keyCode"].Number();
                        }
                    }
                    else
                    {
                        std::string keystring = keyInfo["nativeKeyCode"].String();
                        if (keystring.compare("*") == 0)
                        {
                          keyCode = ANY_KEY;
                        }
                        else
                        {
                          keyCode = keyInfo["nativeKeyCode"].Number();
                        }
                    }

                    const JsonArray modifiers = keyInfo.HasLabel("modifiers") ? keyInfo["modifiers"].Array() : JsonArray();
                    uint32_t flags = 0;
                    for (int i=0; i<modifiers.Length(); i++) {
                      flags |= getKeyFlag(modifiers[i].String());
                    }

                    if (keyInfo.HasLabel("keyCode"))
                    {
                        result = CompositorController::removeKeyListener(client, keyCode, flags);
                    }
                    else
                    {
                        result = CompositorController::removeNativeKeyListener(client, keyCode, flags);
                    }
                }
                else
                {
                    std::cout << "ERROR: Neither keyCode nor nativeKeyCode provided" << std::endl;
                }

                if (result == false)
                {
                    break;
                }
            }
            gRdkShellMutex.unlock();
            return result;
        }

        bool RDKShell::injectKey(const uint32_t& keyCode, const JsonArray& modifiers)
        {
            bool ret = false;
            uint32_t flags = 0;
            for (int i=0; i<modifiers.Length(); i++) {
              flags |= getKeyFlag(modifiers[i].String());
            }
            gRdkShellMutex.lock();
            ret = CompositorController::injectKey(keyCode, flags);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::generateKey(const JsonArray& keyInputs)
        {
            bool ret = false;
            for (int i=0; i<keyInputs.Length(); i++) {
                const JsonObject& keyInputInfo = keyInputs[i].Object();
                if (keyInputInfo.HasLabel("keyCode"))
                {
                  const uint32_t keyCode = keyInputInfo["keyCode"].Number();
                  const uint32_t delay = keyInputInfo["delay"].Number();
                  sleep(delay);
                  const JsonArray modifiers = keyInputInfo.HasLabel("modifiers") ? keyInputInfo["modifiers"].Array() : JsonArray();
                  uint32_t flags = 0;
                  for (int k=0; k<modifiers.Length(); k++) {
                    flags |= getKeyFlag(modifiers[k].String());
                  }
                  gRdkShellMutex.lock();
                  ret = CompositorController::injectKey(keyCode, flags);
                  gRdkShellMutex.unlock();
                }
            }
            return ret;
        }

        bool RDKShell::getScreenResolution(JsonObject& out)
        {
            unsigned int width=0,height=0;
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::getScreenResolution(width, height);
            gRdkShellMutex.unlock();
            if (true == ret) {
              out["w"] = width;
              out["h"] = height;
              return true;
            }
            return false;
        }

        bool RDKShell::setScreenResolution(const unsigned int w, const unsigned int h)
        {
            gRdkShellMutex.lock();
            receivedResolutionRequest = true;
            resolutionWidth = w;
            resolutionHeight = h;
            gRdkShellMutex.unlock();
            return true;
        }

        bool RDKShell::setMimeType(const string& client, const string& mimeType)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::setMimeType(client, mimeType);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::getMimeType(const string& client, string& mimeType)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::getMimeType(client, mimeType);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::createDisplay(const string& client, const string& displayName)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::createDisplay(client, displayName);
            RdkShell::CompositorController::addListener(client, mEventListener);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::getClients(JsonArray& clients)
        {
            std::vector<std::string> clientList;
            gRdkShellMutex.lock();
            CompositorController::getClients(clientList);
            gRdkShellMutex.unlock();
            for (size_t i=0; i<clientList.size(); i++) {
              clients.Add(clientList[i]);
            }
            return true;
        }

        bool RDKShell::getZOrder(JsonArray& clients)
        {
            std::vector<std::string> zOrderList;
            gRdkShellMutex.lock();
            CompositorController::getZOrder(zOrderList);
            gRdkShellMutex.unlock();
            for (size_t i=0; i<zOrderList.size(); i++) {
              clients.Add(zOrderList[i]);
            }
            return true;
        }

        bool RDKShell::getBounds(const string& client, JsonObject& bounds)
        {
            unsigned int x=0,y=0,width=0,height=0;
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::getBounds(client, x, y, width, height);
            gRdkShellMutex.unlock();
            if (true == ret) {
              bounds["x"] = x;
              bounds["y"] = y;
              bounds["w"] = width;
              bounds["h"] = height;
              return true;
            }
            return false;
        }

        bool RDKShell::setBounds(const std::string& client, const unsigned int x, const unsigned int y, const unsigned int w, const unsigned int h)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::setBounds(client, x, y, w, h);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::getVisibility(const string& client, bool& visible)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::getVisibility(client, visible);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::setVisibility(const string& client, const bool visible)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::setVisibility(client, visible);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::getOpacity(const string& client, unsigned int& opacity)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::getOpacity(client, opacity);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::setOpacity(const string& client, const unsigned int opacity)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::setOpacity(client, opacity);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::getScale(const string& client, double& scaleX, double& scaleY)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::getScale(client, scaleX, scaleY);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::setScale(const string& client, const double scaleX, const double scaleY)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::setScale(client, scaleX, scaleY);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::getHolePunch(const string& client, bool& holePunch)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::getHolePunch(client, holePunch);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::setHolePunch(const string& client, const bool holePunch)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::setHolePunch(client, holePunch);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::removeAnimation(const string& client)
        {
            bool ret = false;
            gRdkShellMutex.lock();
            ret = CompositorController::removeAnimation(client);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::addAnimationList(const JsonArray& animations)
        {
            gRdkShellMutex.lock();
            for (int i=0; i<animations.Length(); i++) {
                const JsonObject& animationInfo = animations[i].Object();
                if (animationInfo.HasLabel("client") && animationInfo.HasLabel("duration"))
                {
                    const string client  = animationInfo["client"].String();
                    const double duration = std::stod(animationInfo["duration"].String());
                    std::map<std::string, RdkShellData> animationProperties;
                    if (animationInfo.HasLabel("x"))
                    {
                        int32_t x = animationInfo["x"].Number();
                        animationProperties["x"] = x;
                    }
                    if (animationInfo.HasLabel("y"))
                    {
                        int32_t y = animationInfo["y"].Number();
                        animationProperties["y"] = y;
                    }
                    if (animationInfo.HasLabel("w"))
                    {
                        uint32_t width = animationInfo["w"].Number();
                        animationProperties["w"] = width;
                    }
                    if (animationInfo.HasLabel("h"))
                    {
                        uint32_t height = animationInfo["h"].Number();
                        animationProperties["h"] = height;
                    }
                    if (animationInfo.HasLabel("sx"))
                    {
                        double scaleX = std::stod(animationInfo["sx"].String());
                        animationProperties["sx"] = scaleX;
                    }
                    if (animationInfo.HasLabel("sy"))
                    {
                        double scaleY = std::stod(animationInfo["sy"].String());
                        animationProperties["sy"] = scaleY;
                    }
                    if (animationInfo.HasLabel("a"))
                    {
                        uint32_t opacity = animationInfo["a"].Number();
                        animationProperties["a"] = opacity;
                    }
                    if (animationInfo.HasLabel("tween"))
                    {
                        std::string tween = animationInfo["tween"].String();
                        animationProperties["tween"] = tween;
                    }
                    CompositorController::addAnimation(client, duration, animationProperties);
                }
            }
            gRdkShellMutex.unlock();
            return true;
        }

        bool RDKShell::enableInactivityReporting(const bool enable)
        {
            gRdkShellMutex.lock();
            CompositorController::enableInactivityReporting(enable);
            gRdkShellMutex.unlock();
            return true;
        }

        bool RDKShell::setInactivityInterval(const uint32_t interval)
        {
            gRdkShellMutex.lock();
            try
            {
              CompositorController::setInactivityInterval((double)interval);
            }
            catch (...) 
            {
              std::cout << "RDKShell unable to set inactivity interval  " << std::endl;
            }
            gRdkShellMutex.unlock();
            return true;
        }

        void RDKShell::onLaunched(const std::string& client, const string& launchType)
        {
            std::cout << "RDKShell onLaunched event received for " << client << std::endl;
            JsonObject params;
            params["client"] = client;
            params["launchType"] = launchType;
            notify(RDKSHELL_EVENT_ON_LAUNCHED, params);
        }

        void RDKShell::onSuspended(const std::string& client)
        {
            std::cout << "RDKShell onSuspended event received for " << client << std::endl;
            JsonObject params;
            params["client"] = client;

            notify(RDKSHELL_EVENT_ON_SUSPENDED, params);
        }

        void RDKShell::onDestroyed(const std::string& client)
        {
            std::cout << "RDKShell onDestroyed event received for " << client << std::endl;
            JsonObject params;
            params["client"] = client;
            notify(RDKSHELL_EVENT_ON_DESTROYED, params);
        }

        bool RDKShell::systemMemory(uint32_t &freeKb, uint32_t & totalKb, uint32_t & usedSwapKb)
        {
            gRdkShellMutex.lock();
            bool ret = RdkShell::systemRam(freeKb, totalKb, usedSwapKb);
            gRdkShellMutex.unlock();
            return ret;
        }

        bool RDKShell::pluginMemoryUsage(const string callsign, JsonArray& memoryInfo)
        {
            JsonObject memoryDetails;
            Exchange::IMemory* pluginMemoryInterface(mCurrentService->QueryInterfaceByCallsign<Exchange::IMemory>(callsign.c_str()));
            memoryDetails["callsign"] = callsign;
            memoryDetails["ram"] = -1;
            if (nullptr != pluginMemoryInterface)
            {
                memoryDetails["ram"] = pluginMemoryInterface->Resident()/1024;
            }
            else
            {
                std::cout << "Memory information not available for " << callsign << std::endl;
            }
            memoryInfo.Add(memoryDetails);
            return true;
        }


        PluginStateChangeData::PluginStateChangeData(std::string callsign, std::shared_ptr<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement>> pluginConnection, RDKShell* rdkshell):mCallSign(callsign), mRDKShell(*rdkshell)
        {
            mPluginConnection = pluginConnection;
            mLaunchEnabled = false;
        }

        PluginStateChangeData::~PluginStateChangeData()
        {
            mPluginConnection = nullptr;
        }

        void PluginStateChangeData::enableLaunch(bool enable)
        {
            mLaunchEnabled = enable;
        }

        void PluginStateChangeData::onStateChangeEvent(const JsonObject& params)
        {
            bool isSuspended = params["suspended"].Boolean();
            if (mLaunchEnabled)
            {
               JsonObject params;
               params["client"] = mCallSign;
               params["launchType"] = (isSuspended)?"suspend":"resume";
               mRDKShell.notify(RDKShell::RDKSHELL_EVENT_ON_LAUNCHED, params);
               mLaunchEnabled = false;
            }

            if (isSuspended)
            {
                JsonObject params;
                params["client"] = mCallSign;
                mRDKShell.notify(RDKShell::RDKSHELL_EVENT_ON_SUSPENDED, params);
            }
        }

        // Internal methods end
    } // namespace Plugin
} // namespace WPEFramework
