﻿# ifndef __Layer_meal__
# define __Layer_meal__

# include "../LayerBase.h"

# include "ui/CocosGUI.h"

namespace User
{
    class Layer_meal : public LayerBase
    {
    protected:
        void confirmButton( );//決定ボタンを表示する
                              //void backButton();//ホームに戻るボタン

        void eatText( );//食材説明用ウィンドウ

        void foodText( std::string commentary, int x, int y, int size);//食材説明
        void eraseFoodText( );

        //void eatButton(int food_num);//食材描画用 仮引数で描画するものを変更

        void Menu( );//選択用ウィンドウ
        void selectedItemEvent( Ref *pSender, cocos2d::ui::ListView::EventType type );

        void eatTime( std::string eatTime );//時間表示？

        void character(std::string chara_texture, std::string puppet);//キャラクター描画

		void eraseCharacter();

        void animation( int anime_num );//食事アニメーション

        void normalButton( int text_number, std::string button_photo, int normalButtonTag );//ボタン汎用用

        void heart( );//好感度表示(仮)

        void buttonAudio( std::string audio_name, int volume );//効果音読み込み用 volume 0.0~1.0

        void mealDressVolume();//音量調節用

        void mealTutorial( );//チュートリアル用?

        void eraseMealTutorial( );

        void loadData( );

		void loveMetor();

		void dressAnimetion(int my_dress, int dress_num);//現在のドレス番号、着替えのドレス番号

		void dressChange();

		void decoration();//装飾用

    public:
        bool exist;//食べ物画像用
        bool reside;//決定の有無用
        int change;//食事と着替え
		cocos2d::UserDefault * now;
		int now_dress;//今の服
		int next_dress = 0;//着替えた後の服
		int love_degrees = 0;//親愛度受け渡し用
        int audio_volume = 1.0f;
        int animation_num = 0;//アニメーション番号
        cocos2d::Sprite * food;//アニメーション用画像

        enum situation
        {
            meal,
            dressClothes,
        };

        //食べ物画像
        std::vector<std::string> food_button;

        //食べ物取得有無
        std::vector<bool> food_gain;//falseで未取得

        //衣装画像
        std::vector<std::string> dress_button;

        //衣装の有無
        std::vector<bool> dress_gain;//falseで未取得

        //衣装解説
        std::vector<std::string> dress_commentary
        {
            "ワンピース",
            "ドレス",
            "着ぐるみ",
            "修道服",
            "セーラー服",
        };

		std::vector<std::string> dress_text2
		{
			"四角い形のお砂糖。",
			"白くて小さいお花。",
			"甘酸っぱい果物。",
			"カラフルでかわいい形をしたお砂糖。",
			"クリスフィアが食べられる特別な食べ物。",
		};

		std::vector<std::string> dress_text3
		{
			"食べ物としては少し物足りないかも。",
			"香りが強くいい匂いがする。",
			"ジャムにしてもおいしい。",
			"とてもかわいらしい。",
			"不思議と元気があふれてくる。",
		};

        //食べ物解説
        std::vector<std::string> food_commentary
        {
            "角砂糖",
            "スズラン",
            "ブルーベリー",
            "こんぺいとう",
            "シトリン宝石",
        };

		std::vector<std::string> food_text2
		{
			"四角い形のお砂糖。",
			"白くて小さいお花。",
			"甘酸っぱい果物。",
			"カラフルでかわいい形をしたお砂糖。",
			"クリスフィアが食べられる特別な食べ物。",
		};

		std::vector<std::string> food_text3
		{
			"食べ物としては少し物足りないかも。",
			"香りが強くいい匂いがする。",
			"ジャムにしてもおいしい。",
			"とてもかわいらしい。",
			"不思議と元気があふれてくる。",
		};

		//クロエちゃんファッションショー
		std::vector<std::string> fashion_show;

		//短髪クロエ
		std::vector<std::string> clear;

        CREATE_ARGS_FUNC( Layer_meal );
		Layer_meal();
        Layer_meal( int layer );
        ~Layer_meal( );

        bool init( )override;
        void setup( ) override;
        void update( float delta ) override;

        void setLayer( int _layerName );
    };
}

# endif // __Layer_meal__