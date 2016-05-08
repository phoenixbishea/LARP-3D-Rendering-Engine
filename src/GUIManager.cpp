#include "GUIManager.hpp"




GUIManager::GUIManager(Larp::SceneGraphPtr g, GLFWwindow* window):
_graph(g), _window(window)
{
	this->_renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
	this->_wmgr =  &CEGUI::WindowManager::getSingleton();
	// this->_renderer->setupExtraStates();
	// this->_renderer->enableExtraStateSettings(true);

	this->setup_resources();
	this->setup_menus();
}

GUIManager::~GUIManager()
{

}

void GUIManager::setup_resources()
{
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
   (CEGUI::System::getSingleton().getResourceProvider());


  rp->setResourceGroupDirectory("schemes", "assets/CEGUI/schemes/");
	rp->setResourceGroupDirectory("imagesets", "assets/CEGUI/imagesets/");
	rp->setResourceGroupDirectory("fonts", "assets/CEGUI/fonts/");
	rp->setResourceGroupDirectory("layouts", "assets/CEGUI/layouts/");
	rp->setResourceGroupDirectory("looknfeels", "assets/CEGUI/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", "assets/CEGUI/lua_scripts/");

	/* Setups all the resources */
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

	/* Using the TahrezLook since it is prebuilt. May change for custom gui */
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	CEGUI::FontManager::getSingleton().createFromFile( "DejaVuSans-10.font" );


}

void GUIManager::setup_menus()
{
	/* Main menu sheet */
	CEGUI::Window* mainSheet = this->_wmgr->createWindow("DefaultWindow", "mainSheet");

	/* The Add light button and the menu bar that holds all the add light buttons */
	CEGUI::Window* addLight = this->_wmgr->createWindow("TaharezLook/Button", "addLight");
	CEGUI::Window* lightMenu = this->_wmgr->createWindow("TaharezLook/Menubar", "lightMenu");

	/* All the add light buttons */
	CEGUI::Window* pointLight = this->_wmgr->createWindow("TaharezLook/MenuItem", "point");
	CEGUI::Window* spotLight = this->_wmgr->createWindow("TaharezLook/MenuItem", "spot");
	CEGUI::Window* directionalLight = this->_wmgr->createWindow("TaharezLook/MenuItem", "directional");

	/* This is the quit button*/
	CEGUI::Window* quit = this->_wmgr->createWindow("TaharezLook/Button", "quit");


	CEGUI::Window* lightList = this->_wmgr->createWindow("TaharezLook/ScrollablePane", "lightList");

	CEGUI::Window* pushTest1 = this->_wmgr->createWindow("TaharezLook/Button", "txt");
	CEGUI::Window* pushTest2 = this->_wmgr->createWindow("TaharezLook/Button", "txt2");

	CEGUI::Window* lightEdit = this->_wmgr->createWindow("TaharezLook/ScrollablePane", "lightEdit");

	CEGUI::Spinner* testSpinner = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "spinner"));

	/* Color for the lights */
	CEGUI::Spinner* redSpinner = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "red"));
	CEGUI::Spinner* greenSpinner = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "green"));
	CEGUI::Spinner* blueSpinner = static_cast<CEGUI::Spinner*>(this->_wmgr->createWindow("TaharezLook/Spinner", "blue"));

	redSpinner->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	redSpinner->setMinimumValue(0.0f);
	redSpinner->setMaximumValue(255.0f);
	redSpinner->setStepSize(10.0f);
	redSpinner->setCurrentValue(10.0f);
	redSpinner->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(0.0f,0)));

	greenSpinner->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	greenSpinner->setMinimumValue(0.0f);
	greenSpinner->setMaximumValue(255.0f);
	greenSpinner->setStepSize(10.0f);
	greenSpinner->setCurrentValue(10.0f);
	greenSpinner->setPosition(CEGUI::UVector2(CEGUI::UDim(0.12f,0),CEGUI::UDim(0.0f,0)));

	blueSpinner->setTextInputMode(CEGUI::Spinner::FloatingPoint);
	blueSpinner->setMinimumValue(0.0f);
	blueSpinner->setMaximumValue(255.0f);
	blueSpinner->setStepSize(10.0f);
	blueSpinner->setCurrentValue(10.0f);
	blueSpinner->setPosition(CEGUI::UVector2(CEGUI::UDim(0.24f,0),CEGUI::UDim(0.0f,0)));


	lightEdit->setSize(CEGUI::USize(CEGUI::UDim(0.75,0), CEGUI::UDim(0.45,0)));
	lightEdit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5,0),CEGUI::UDim(0.4f,0)));

	lightList->setSize(CEGUI::USize(CEGUI::UDim(0.75,0), CEGUI::UDim(0.45,0)));
	lightList->setPosition(CEGUI::UVector2(CEGUI::UDim(0.35f,0),CEGUI::UDim(0.4f,0)));

	pushTest1->setText("Hi thar");
	pushTest1->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	pushTest2->setText("Das Kampfer");
	pushTest2->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	pushTest2->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(0.05f,0)));

	lightList->addChild(pushTest1);
	lightList->addChild(pushTest2);

	lightEdit->addChild(redSpinner);
	lightEdit->addChild(greenSpinner);
	lightEdit->addChild(blueSpinner);

	this->_light_edit.push_back(redSpinner);
	this->_light_edit.push_back(greenSpinner);
	this->_light_edit.push_back(blueSpinner);



	pointLight->setText("Point Light");
	spotLight->setText("Spotlight");
	directionalLight->setText("Directional Light");


  lightMenu->setPosition(CEGUI::UVector2(CEGUI::UDim(0.4f,0),CEGUI::UDim(0.4f,0)));
  lightMenu->setSize(CEGUI::USize(CEGUI::UDim(0.25,0), CEGUI::UDim(0.05,0)));

  addLight->setText("Add Light...");
  addLight->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05f,0),CEGUI::UDim(0.2f,0)));
  addLight->setSize(CEGUI::USize(CEGUI::UDim(0.10,0), CEGUI::UDim(0.05,0)));


  quit->setText("Quit");
  quit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05f,0),CEGUI::UDim(0.6f,0)));
  quit->setSize(CEGUI::USize(CEGUI::UDim(0.10,0), CEGUI::UDim(0.05,0)));

  addLight->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::add_light, this));
  pointLight->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::add_point_light, this));
  spotLight->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::add_spot_light, this));
  directionalLight->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::add_directional_light, this));
  pushTest1->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::push_test, this));
  pushTest2->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::push_test, this));


  quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::quit, this));

  lightMenu->addChild(pointLight);
  lightMenu->addChild(spotLight);
  lightMenu->addChild(directionalLight);

  this->populate_light_list(lightList);

  mainSheet->addChild(addLight);
  mainSheet->addChild(quit);
  mainSheet->addChild(lightList);
  // mainSheet->addChild(testSpinner);

  this->_sheets.push_back(mainSheet);
  this->_sheets.push_back(lightMenu);
  this->_sheets.push_back(lightList);
  this->_sheets.push_back(lightEdit);

  this->_light_list.push_back(pushTest1);
  this->_light_list.push_back(pushTest2);


  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mainSheet);
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
}

void GUIManager::populate_light_list(CEGUI::Window* lightList)
{
	// /* Create buttons for each directional light */
	// CEGUI::Window* temp;
	// std::string tempName;
	// for(uint n = 0; n < LightFactory::_directional_lights.size(); ++n)
	// {
	// 	tempName = "directionalLight" + n;

	// 	/*setups the window button */
	// 	temp = this->_wmgr->createWindow("TaharezLook/Button", tempName);
	// 	temp->setText(tempName);
	// 	temp->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	// 	temp->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(this->yPos,0)));
	// 	temp->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::push_test, this));

	// 	/*Adds the button to the light list and maps the name of the light to the directional light */
	// 	lightList->addChild(temp);
	// 	this->_light_list.push_back(temp);
	// 	this->_direct_map.emplace(tempName, LightFactor::_directional_lights.at(n));
	// 	this->yPos += 0.05;
	// }

	// /* Create buttons for each point lights */
	// for(n = 0; n < LightFactory::_point_lights.size(); ++n)
	// {
	// 	tempName = "pointLight" + n;

	// 	/*setups the window button */
	// 	temp = this->_wmgr->createWindow("TaharezLook/Button", tempName);
	// 	temp->setText(tempName);
	// 	temp->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	// 	temp->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(this->yPos,0)));
	// 	temp->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::push_test, this));

	// 	/*Adds the button to the light list and maps the name of the light to the directional light */
	// 	lightList->addChild(temp);
	// 	this->_light_list.push_back(temp);
	// 	this->_point_map.emplace(tempName, LightFactor::_point_lights.at(n));
	// 	this->yPos += 0.05;
	// }
	// /*Create buttons for each spot light */
	// for(n = 0; n < LightFactory::_spot_lights.size(); ++n)
	// {
	// 	tempName = "spotLight" + n;

	// 	/*setups the window button */
	// 	temp = this->_wmgr->createWindow("TaharezLook/Button", tempName);
	// 	temp->setText(tempName);
	// 	temp->setSize(CEGUI::USize(CEGUI::UDim(0.1,0), CEGUI::UDim(0.05,0)));
	// 	temp->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0),CEGUI::UDim(this->yPos,0)));
	// 	temp->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUIManager::push_test, this));

	// 	/*Adds the button to the light list and maps the name of the light to the directional light */
	// 	lightList->addChild(temp);
	// 	this->_light_list.push_back(temp);
	// 	this->_point_map.emplace(tempName, LightFactor::_spot_lights.at(n));
	// 	this->yPos += 0.05;
	// }
}

bool GUIManager::get_rendering_state()
{
	return this->_GUI_rendering;
}

void GUIManager::add_light(const CEGUI::EventArgs&)
{
		this->_sheets.at(MAIN)->addChild(this->_sheets.at(ADDLIGHT));
}

void GUIManager::add_point_light(const CEGUI::EventArgs&)
{

	this->_sheets.at(MAIN)->removeChild("lightMenu");
	this->hide_GUI();
	Larp::PointLightPtr point_light = this->_graph->create_point_light();

	point_light->set_ambient_intensity(0.0f, 1.0f, 0.0f);
  point_light->set_position(0.0f, 2.0f, 0.0f);

}

void GUIManager::add_spot_light(const CEGUI::EventArgs&)
{

	this->_sheets.at(MAIN)->removeChild("lightMenu");
	this->hide_GUI();

	Larp::SpotLightPtr spot_light = this->_graph->create_spot_light();

	spot_light->set_ambient_intensity(0.0f, 1.0f, 0.0f);
 	spot_light->set_position(0.0f, 2.0f, 0.0f);

}

void GUIManager::add_directional_light(const CEGUI::EventArgs&)
{

	this->_sheets.at(MAIN)->removeChild("lightMenu");
	this->hide_GUI();

	Larp::DirectionalLightPtr directional_light = this->_graph->create_directional_light();

	// directional_light->set_ambient_intensity(0.0f, 1.0f, 0.0f);
 // 	directional_light->set_position(0.0f, 2.0f, 0.0f);

}

void GUIManager::quit(const CEGUI::EventArgs&)
{
	glfwSetWindowShouldClose(this->_window, GL_TRUE);
}
	
void GUIManager::push_test(const CEGUI::EventArgs&)
{
	for(uint i = 0; i < this->_light_list.size(); ++i)
	{
		if(this->_light_list.at(i)->isCapturedByThis())
		{
			this->_sheets.at(MAIN)->addChild(this->_sheets.at(LIGHTEDIT));
		}
	}
}

void GUIManager::hide_GUI()
{
	this->_sheets.at(MAIN)->hide();
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
	this->_GUI_rendering = false;
}

void GUIManager::show_GUI()
{
		this->_sheets.at(MAIN)->show();
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
		this->_GUI_rendering = true;
}

void GUIManager::show_main()
{
	if(_GUI_rendering)
		this->hide_GUI();
	else
		this->show_GUI();

}