
#include "UIManager.h"
#include "BGManager.h"
#include "FGManager.h"

#include "../SceneManager.h"
#include "json/rapidjson.h"
#include "json/document.h"

#include "LayerCleaning.h"
#include "../Diary/LayerDiary.h"
#include "../Ishibashi/Layer_ishibashi.h"

#include "../CiryMap/LayerOption.h"
#include "LayerManager.h"

USING_NS_CC;

namespace User
{
	UIManager::UIManager() :
		winSize(Director::getInstance()->getVisibleSize()),
		origin(Director::getInstance()->getVisibleOrigin()),
		pos(Director::getInstance()->getVisibleSize()),
		menuWindow(nullptr),
		swicthWindow(nullptr),
		optionIcon(nullptr),
		isOpen(false),
		menuButtons(std::vector<ui::Button*>()),
		subButtons(std::vector<ui::Button*>()),
		sliderBers(std::vector<ui::Slider*>()),
		optionLabels(std::vector<Label*>())
	{
		bgManager = BGManager::create();
	}

	UIManager::~UIManager() {}

	bool UIManager::init()
	{
		if (!Layer::init()) { return false; }

		createSubMenuWindow();
		createMainMenuWindow();

		return true;
	}

	void UIManager::createMainMenuWindow()
	{
		auto layout = ui::Layout::create();
		layout->setPosition(Vec2(pos.x * 0, pos.y * 0.f));
		layout->setContentSize(Size(winSize.x,210));

		//���j���[�̔w�i
		auto menuImage = ui::Scale9Sprite::create("res/texture/system/select.base.png",
			Rect(0 / CC_CONTENT_SCALE_FACTOR(), 0 / CC_CONTENT_SCALE_FACTOR(),
				960 / CC_CONTENT_SCALE_FACTOR(), 200 / CC_CONTENT_SCALE_FACTOR()),
			Rect(20 / CC_CONTENT_SCALE_FACTOR(), 20 / CC_CONTENT_SCALE_FACTOR(),
				920 / CC_CONTENT_SCALE_FACTOR(), 160 / CC_CONTENT_SCALE_FACTOR()));
		menuImage->setPosition(layout->getContentSize().width / 2, layout->getContentSize().height * 0.5f);
		menuImage->setContentSize(layout->getContentSize());
		layout->addChild(menuImage);
		Vec2 menuLayout = layout->getContentSize();

		//json�t�@�C���̓ǂݍ���
		auto fileUtils = FileUtils::getInstance();
		auto path = fileUtils->getStringFromFile(u8"res/json/mainMenuUI.json");
		rapidjson::Document doc;

		//json�t�@�C�����p�[�X
		doc.Parse<rapidjson::kParseDefaultFlags>(path.c_str());

		if (!doc.HasParseError())
		{
			const rapidjson::Value& buttonsData = doc["Button"];
			for (rapidjson::SizeType i = 0; i < buttonsData.Size(); i++)
			{
				menuButtons.push_back(ui::Button::create(buttonsData[i]["res"]["pull"].GetString(), buttonsData[i]["res"]["push"].GetString(), buttonsData[i]["res"]["pull"].GetString()));
				menuButtons[i]->setTitleFontSize(42);
				menuButtons[i]->setTitleColor(Color3B::WHITE);

				float x = buttonsData[i]["pos"]["x"].GetDouble();
				float y = buttonsData[i]["pos"]["y"].GetDouble();

				menuButtons[i]->setPosition(Vec2(menuLayout.x * x, menuLayout.y * y));
				layout->addChild(menuButtons[i], 1, i);

				menuButtons[i]->addTouchEventListener(CC_CALLBACK_2(UIManager::touchEventOfMainMenu, this));
			}
		}
		this->addChild(layout, (int)zOder::MENU, (int)tabMenu::MAIN_MENU);
	}

	//�琬���j���[�̏���
	void UIManager::createSubMenuWindow()
	{
		auto layout = ui::Layout::create();
		layout->setPosition(Vec2(pos.x, pos.y * 0));
		layout->setContentSize(Size(winSize.x, 210));

		//���j���[�̔w�i
		auto menuImage = ui::Scale9Sprite::create("res/texture/system/select.base.png",
			Rect(0 / CC_CONTENT_SCALE_FACTOR(), 0 / CC_CONTENT_SCALE_FACTOR(),
				960 / CC_CONTENT_SCALE_FACTOR(), 200 / CC_CONTENT_SCALE_FACTOR()),
			Rect(20 / CC_CONTENT_SCALE_FACTOR(), 20 / CC_CONTENT_SCALE_FACTOR(),
				920 / CC_CONTENT_SCALE_FACTOR(), 160 / CC_CONTENT_SCALE_FACTOR()));
		menuImage->setPosition(layout->getContentSize().width / 2, layout->getContentSize().height * 0.5f);
		menuImage->setContentSize(layout->getContentSize());
		layout->addChild(menuImage);
		Vec2 menuLayout = layout->getContentSize();

		//json�t�@�C���̓ǂݍ���
		auto fileUtils = FileUtils::getInstance();
		auto path = fileUtils->getStringFromFile("res/json/subMenuUI.json");
		rapidjson::Document doc;

		//json�t�@�C�����p�[�X
		doc.Parse<rapidjson::kParseDefaultFlags>(path.c_str());

		if (!doc.HasParseError())
		{
			const rapidjson::Value& buttonsData = doc["Button"];
			for (rapidjson::SizeType i = (int)SubButtonType::BACK; i < buttonsData.Size(); i++)
			{
				subButtons.push_back(ui::Button::create( buttonsData[i]["res"]["pull"].GetString(), buttonsData[i]["res"]["push"].GetString(), buttonsData[i]["res"]["pull"].GetString()) );
				subButtons[i]->setTitleFontSize(42);
				subButtons[i]->setTitleColor(Color3B::WHITE);

				float x = buttonsData[i]["pos"]["x"].GetDouble();
				float y = buttonsData[i]["pos"]["y"].GetDouble();

				subButtons[i]->setPosition(Vec2(menuLayout.x * x, menuLayout.y * y));
				layout->addChild(subButtons[i], 1, i + (int)SubButtonType::BACK);

				subButtons[i]->addTouchEventListener(CC_CALLBACK_2(UIManager::touchEventOfSubMenu, this));
			}
		}
		this->addChild(layout, (int)zOder::MENU, (int)tabMenu::BREEDING_MENU);
	}

	//�e���j���[�{�^���̏���
	void UIManager::touchEventOfMainMenu(Ref * pSender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: break;
		case ui::Widget::TouchEventType::ENDED:

			if (pSender == menuButtons[(int)ButtonType::STORY]) {
				SceneManager::createCityMap();
				break;
			}
			if (pSender == menuButtons[(int)ButtonType::BREEDING]) {
				changeToSubWindow();
				break;
			}
			if (pSender == menuButtons[(int)ButtonType::OPTION]) {
				setOptionWindow();
				break;
			}
			if (pSender == menuButtons[(int)ButtonType::DIARY]) {
				changeToDiaryWindow();
				break;
			}

		default:
			break;
		}

		for (auto& it : menuButtons) {
			it->runAction(Sequence::create(CallFunc::create([=] {it->setEnabled(false); }),
				DelayTime::create(4),
				CallFunc::create([=] {it->setEnabled(true); }),
				nullptr));
		}

	}

	//�琬���j���[�̃{�^������
	void UIManager::touchEventOfSubMenu(Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN: break;
		case ui::Widget::TouchEventType::CANCELED: break;
		case ui::Widget::TouchEventType::ENDED:
			if (pSender == subButtons[(int)SubButtonType::BACK]) {
				changeToMainWindow();
				break;
			}
			if (pSender == subButtons[(int)SubButtonType::MEAL]) {
				changeToBreeding(0);
				break;
			}
			if (pSender == subButtons[(int)SubButtonType::CLOTHES]) {
				changeToBreeding(1);
				break;
			}
			if (pSender == subButtons[(int)SubButtonType::CLEANING]) {
				changeToCreaning();
				break;
			}
		default:
			break;
		}
	}

	//�琬���j���[���烁�C�����j���[�֖߂��֐��ł�
	void UIManager::changeToMainWindow()
	{
		auto m = this->getChildByTag((int)tabMenu::MAIN_MENU);
		auto s = this->getChildByTag((int)tabMenu::BREEDING_MENU);
		swapWindow(s, m);

		//���݂̃V�[�����擾���A�V�[������addChild����Ă���BGManager�ɃA�N�Z�X���Ċ֐����Ăяo���B
		auto p = this->getParent();
		auto c = (BGManager*)p->getChildByTag((int)tabLayer::BACKGROUND);
		c->changeBackGround((int)tabMenu::MAIN_MENU, (int)tabMenu::BREEDING_MENU);
	}

	//���C�����j���[����T�u���j���[�֕ύX����֐��ł�
	void UIManager::changeToSubWindow()
	{
		auto m = this->getChildByTag((int)tabMenu::MAIN_MENU);
		auto s = this->getChildByTag((int)tabMenu::BREEDING_MENU);
		swapWindow(m, s);

		auto p = this->getParent();
		auto c = (BGManager*)p->getChildByTag((int)tabLayer::BACKGROUND);
		c->changeBackGround((int)tabMenu::BREEDING_MENU, (int)tabMenu::MAIN_MENU);
	}

	//���L��ʂֈړ�
	void UIManager::changeToDiaryWindow()
	{
		float fadeTime(3);
		auto p = this->getParent();
		auto f = (FGManager*)p->getChildByTag((int)tabLayer::FOREGROUND);
		this->runAction(Sequence::create(CallFunc::create([=] {f->fading(fadeTime); }),
			DelayTime::create(fadeTime / 2),
			CallFunc::create([this] {
			auto p = this->getParent();
			auto layer = LayerDiary::create();
			layer->setName(typeid(LayerDiary).name());
			layer->setPosition(Vec2(winSize * 0.f));
			p->addChild(layer, (int)tabMenu::DIARY_MENU, (int)tabLayer::DIARY);
			p->removeChildByTag((int)tabLayer::UI_MANAGER); }),
			nullptr));
	}

	//�|����ʂ̃��C���[�ɓ\��ւ�
	void UIManager::changeToCreaning()
	{
		auto p = this->getParent();
		p->removeChildByTag((int)tabLayer::CHARACTER);
		p->removeChildByTag((int)tabLayer::UI_MANAGER);
		p->removeChildByTag((int)tabLayer::BACKGROUND);
		p->addChild(LayerCleaning::create(), 0, (int)tabLayer::CLEANING);
	}

	//�H����ʋy�ђ��ւ���ʂֈړ�----------------------------------------------------------------------
	void UIManager::changeToBreeding(int _menuId)
	{
		float fadeTime(2);
		auto p = this->getParent();
		auto f = (FGManager*)p->getChildByTag((int)tabLayer::FOREGROUND);
		this->runAction(Sequence::create(CallFunc::create([=] {f->fading(fadeTime); }),
			DelayTime::create(fadeTime / 2),
			CallFunc::create([=] {
			p->removeChildByTag((int)tabLayer::CHARACTER);
			p->removeChildByTag((int)tabLayer::UI_MANAGER);
			p->addChild(Layer_meal::create(_menuId), 0, (int)tabLayer::CLEANING); }),
			nullptr));
	}

	//���C���[�����ւ���֐��ł��B���݂�Node�̎w�肵���ł��Ȃ��ł�
	//TODO:Pos�w��A�ړ����Ԃ̎w��A�x�����Ԃ̎w����ł���悤�ɂ���B
	void UIManager::swapWindow(Node * moveOutObj, Node * moveInObj)
	{
		auto size = Director::getInstance()->getVisibleSize();
		auto moveOut = MoveBy::create(0.3f, Vec2(size.width, 0));
		moveOutObj->runAction(moveOut);

		auto moveIn = MoveBy::create(0.3f, Vec2(-size.width, 0));
		auto delay = DelayTime::create(0.5f);
		moveInObj->runAction(Sequence::create(delay, moveIn, nullptr));
	}

	//�I�v�V�����E�B���h�E�̐���
	//TODO:Pos�w��ASize�w��A�摜�w����ł���悤�ɂ���B
	void UIManager::setOptionWindow()
	{
		float fadeTime(2);
		auto p = this->getParent();
		auto f = (FGManager*)p->getChildByTag((int)tabLayer::FOREGROUND);
		this->runAction(Sequence::create(CallFunc::create([=] {f->fading(fadeTime); }),
			DelayTime::create(fadeTime / 2),
			CallFunc::create([=] {
			p->addChild(LayerOption::create(), 4); }),
			nullptr));
	}
}
