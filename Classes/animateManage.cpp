#include "animateManage.h"

Animate* animateManage::createAnimate(const char *fileName, int frame, int fps)
{
	auto texture = Sprite::create(fileName);
	float h = texture->getContentSize().height;
	float w = texture->getContentSize().width / frame;

	auto animation = Animation::create();
	for (int i = 0; i < frame; ++i){
		auto spriteFrame = SpriteFrame::create(fileName, Rect(i*w, 0, w, h));
		animation->addSpriteFrame(spriteFrame);
	}
	animation->setDelayPerUnit(1.0f / fps);

	auto animate = Animate::create(animation);
	return animate;
}