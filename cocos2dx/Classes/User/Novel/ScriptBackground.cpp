#include "ScriptBackground.h"

USING_NS_CC;

namespace User
{
    ScriptBackground::ScriptBackground( cocos2d::Layer* layer, std::string textureName )
        : ScriptBase( layer )
        , textureName( textureName )
    {
        REGIST_SCRIPT( u8"in", ScriptBackground::in );
        REGIST_SCRIPT( u8"out", ScriptBackground::out );
        REGIST_SCRIPT( u8"fadein", ScriptBackground::fadein );
        REGIST_SCRIPT( u8"fadeout", ScriptBackground::fadeout );
        REGIST_SCRIPT( u8"circlein", ScriptBackground::circlein );
        REGIST_SCRIPT( u8"circleout", ScriptBackground::circleout );
    }
    ScriptBackground::~ScriptBackground( )
    {

    }
    void ScriptBackground::in( ArgumentList const& args )
    {
        create( );
    }
    void ScriptBackground::out( ArgumentList const & args )
    {
        layer->removeChildByTag( (int)Tag::Background );
    }
    void ScriptBackground::fadein( ArgumentList const & args )
    {
        auto sprite = create( );
        if ( !sprite ) return;

        sprite->setOpacity( 0 );

        auto fade = FadeIn::create( 1.0 );
        sprite->runAction( Sequence::create( fade, nullptr ) );
    }
    void ScriptBackground::fadeout( ArgumentList const & args )
    {
        if ( auto node = layer->getChildByTag( (int)Tag::Background ) )
        {
            auto fade = FadeOut::create( 1.0 );
            auto remove = RemoveSelf::create( );
            node->runAction( Sequence::create( fade, remove, nullptr ) );
        }
    }
    void ScriptBackground::circlein( ArgumentList const & args )
    {
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );

        auto sprite = Sprite::create( "res/texture/novel/" + textureName );
        if ( !sprite ) return;

        sprite->setPosition( origin + visibleSize / 2 );
        auto size = sprite->getContentSize( );
        auto targetSize = Size( visibleSize );
        sprite->setScale( targetSize.height / size.height, targetSize.height / size.height );

        auto clipSprite = Sprite::create( "res/texture/novel/mask.png" );
        if ( !clipSprite ) return;

        clipSprite->setTag( (int)Tag::Background );
        clipSprite->setScale( 0.0 );
        clipSprite->runAction( ScaleTo::create( 2.0, 1.0 ) );
        clipSprite->setPosition( origin + visibleSize / 2 );

        auto clipping = ClippingNode::create( );
        if ( !clipping ) return;

        clipping->setStencil( clipSprite );
        clipping->setInverted( false );
        clipping->setAlphaThreshold( 0.0 );
        clipping->addChild( sprite );

        layer->addChild( clipping );
    }
    void ScriptBackground::circleout( ArgumentList const & args )
    {
        auto origin = Director::getInstance( )->getVisibleOrigin( );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );

        auto sprite = Sprite::create( "res/texture/novel/" + textureName );
        if ( !sprite ) return;

        sprite->setPosition( origin + visibleSize / 2 );
        auto size = sprite->getContentSize( );
        auto targetSize = Size( visibleSize );
        sprite->setScale( targetSize.height / size.height, targetSize.height / size.height );

        auto clipSprite = Sprite::create( "res/texture/novel/mask.png" );
        if ( !clipSprite ) return;

        clipSprite->setTag( (int)Tag::Background );
        clipSprite->setScale( 1.0 );
        clipSprite->runAction( ScaleTo::create( 2.0, -1.0 ) );
        clipSprite->setPosition( origin + visibleSize / 2 );

        auto clipping = ClippingNode::create( );
        if ( !clipping ) return;

        clipping->setStencil( clipSprite );
        clipping->setInverted( false );
        clipping->setAlphaThreshold( 0.0 );
        clipping->addChild( sprite );

        layer->addChild( clipping );
    }
    cocos2d::Sprite * ScriptBackground::create( )
    {
        layer->removeChildByTag( (int)Tag::Background );
        auto visibleSize = Director::getInstance( )->getVisibleSize( );
        auto origin = Director::getInstance( )->getVisibleOrigin( );

        auto sprite = Sprite::create( "res/texture/novel/" + textureName );
        if ( !sprite ) return nullptr;

        sprite->setTag( (int)Tag::Background );
        sprite->setPosition( origin + Vec2( visibleSize.width / 2,
                                            visibleSize.height / 2 ) );

        auto size = sprite->getContentSize( );
        auto targetSize = Size( visibleSize );
        sprite->setScale( targetSize.height / size.height, targetSize.height / size.height );
        layer->addChild( sprite );

        return sprite;
    }
}
