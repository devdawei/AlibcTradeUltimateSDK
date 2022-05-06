//
//  RVALoadRequestEvent.h
//  AriverApp
//
//  Created by chenwenhong on 15/9/23.
//  Copyright © 2015年 Alipay. All rights reserved.
//

//#import <NebulaPoseidon/NebulaPoseidon.h>

@interface RVALoadRequestEvent : RVKEvent

@property(nonatomic, strong) NSURLRequest *request;
@property(nonatomic, assign) BOOL runAutoLoginLogic;

+ (instancetype)allEvent:(NSURLRequest *)request;

+ (instancetype)firstLoadRequstEvent:(NSURLRequest *)request;

@end
