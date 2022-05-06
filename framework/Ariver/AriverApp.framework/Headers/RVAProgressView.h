//
//  RVAProgressView.h
//  AriverApp
//
//  Created by chenwenhong on 15/10/13.
//  Copyright © 2015年 Alipay. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RVAProgressViewProtocol.h"

@interface RVAProgressView : UIView <RVAProgressViewProtocol>

@property(nonatomic) float progress;                        // 0.0 .. 1.0, default is 0.0. values outside are pinned.
@property(nonatomic, strong, nullable) UIColor* progressTintColor; // 0xFF00aaff
@property(nonatomic, strong, nullable) UIColor* trackTintColor; // clearColor

@end
