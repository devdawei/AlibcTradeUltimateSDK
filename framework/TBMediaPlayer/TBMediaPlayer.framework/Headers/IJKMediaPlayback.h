/*
 * IJKMediaPlayback.h
 *
 * Copyright (c) 2013 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of ijkPlayer.
 *
 * ijkPlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ijkPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ijkPlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#ifdef DEBUG
#define debugLog(...) NSLog(__VA_ARGS__)
#define debugMethod() NSLog(@"%s", __func__);
#else
#define debugLog(...)
#define debugMethod()
#endif


typedef NS_ENUM(NSInteger, IJKMPMovieScalingMode) {
    IJKMPMovieScalingModeNone,       // No scaling
    IJKMPMovieScalingModeAspectFit,  // Uniform scale until one dimension fits
    IJKMPMovieScalingModeAspectFill, // Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    IJKMPMovieScalingModeFill        // Non-uniform scale. Both render dimensions will exactly match the visible bounds
};

typedef NS_ENUM(NSInteger, IJKMPMoviePlaybackState) {
    IJKMPMoviePlaybackStateStopped,
    IJKMPMoviePlaybackStatePlaying,
    IJKMPMoviePlaybackStatePaused,
    IJKMPMoviePlaybackStateInterrupted,
    IJKMPMoviePlaybackStateSeekingForward,
    IJKMPMoviePlaybackStateSeekingBackward,
    IJKMPMoviePlaybackStatePrepared
};

typedef NS_OPTIONS(NSUInteger, IJKMPMovieLoadState) {
    IJKMPMovieLoadStateUnknown        = 0,
    IJKMPMovieLoadStatePlayable       = 1 << 0,
    IJKMPMovieLoadStatePlaythroughOK  = 1 << 1, // Playback will be automatically started in this state when shouldAutoplay is YES
    IJKMPMovieLoadStateStalled        = 1 << 2, // Playback will be automatically paused in this state, if started
};

typedef NS_ENUM(NSInteger, IJKMPMovieFinishReason) {
    IJKMPMovieFinishReasonPlaybackEnded,
    IJKMPMovieFinishReasonPlaybackError,
    IJKMPMovieFinishReasonUserExited,
    IJKMPMovieFinishReasonARTPError
};

// -----------------------------------------------------------------------------
// Thumbnails

typedef NS_ENUM(NSInteger, IJKMPMovieTimeOption) {
    IJKMPMovieTimeOptionNearestKeyFrame,
    IJKMPMovieTimeOptionExact
};

@protocol IJKMediaPlayback;

#pragma mark IJKMediaPlayback

@protocol IJKMediaPlayback <NSObject>

- (void)prepareToPlay;
- (void)play;
- (void)pause;
- (void)stop;
- (BOOL)isPlaying;
- (void)shutdown;
- (void)setPauseInBackground:(BOOL)pause;

@property(nonatomic, readonly)  UIView *view;
@property(nonatomic)            NSTimeInterval currentPlaybackTime;
@property(nonatomic, readonly)  NSTimeInterval duration;
@property(nonatomic, readonly)  NSTimeInterval playableDuration;
@property(nonatomic, readonly)  NSInteger bufferingProgress;

@property(nonatomic, readonly)  BOOL isPreparedToPlay;
@property(nonatomic, readonly)  IJKMPMoviePlaybackState playbackState;
@property(nonatomic, readonly)  IJKMPMovieLoadState loadState;

@property(nonatomic, readonly) int64_t numberOfBytesTransferred;

@property(nonatomic, readonly) CGSize naturalSize;
@property(nonatomic) IJKMPMovieScalingMode scalingMode;
@property(nonatomic) BOOL shouldAutoplay;

@property (nonatomic) BOOL allowsMediaAirPlay;
@property (nonatomic) BOOL isDanmakuMediaAirPlay;
@property (nonatomic, readonly) BOOL airPlayMediaActive;

@property (nonatomic) float playbackRate;

- (UIImage *)thumbnailImageAtCurrentTime;

#pragma mark Notifications

#ifdef __cplusplus
#define IJK_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define IJK_EXTERN extern __attribute__((visibility ("default")))
#endif

// -----------------------------------------------------------------------------
//  MPMediaPlayback.h

// Posted when the prepared state changes of an object conforming to the MPMediaPlayback protocol changes.
// This supersedes MPMoviePlayerContentPreloadDidFinishNotification.
IJK_EXTERN NSString *const IJKMPMediaPlaybackIsPreparedToPlayDidChangeNotification;

// -----------------------------------------------------------------------------
//  MPMoviePlayerController.h
//  Movie Player Notifications

// Posted when the scaling mode changes.
IJK_EXTERN NSString* const IJKMPMoviePlayerScalingModeDidChangeNotification;

// Posted when movie playback ends or a user exits playback.
IJK_EXTERN NSString* const IJKMPMoviePlayerPlaybackDidFinishNotification;
IJK_EXTERN NSString* const IJKMPMoviePlayerPlaybackDidFinishReasonUserInfoKey; // NSNumber (IJKMPMovieFinishReason)

// Posted when the playback state changes, either programatically or by the user.
IJK_EXTERN NSString* const IJKMPMoviePlayerPlaybackStateDidChangeNotification;

// Posted when the network load state changes.
IJK_EXTERN NSString* const IJKMPMoviePlayerLoadStateDidChangeNotification;

// Posted when the movie player begins or ends playing video via AirPlay.
IJK_EXTERN NSString* const IJKMPMoviePlayerIsAirPlayVideoActiveDidChangeNotification;

// -----------------------------------------------------------------------------
// Movie Property Notifications

// Calling -prepareToPlay on the movie player will begin determining movie properties asynchronously.
// These notifications are posted when the associated movie property becomes available.
IJK_EXTERN NSString* const IJKMPMovieNaturalSizeAvailableNotification;

// -----------------------------------------------------------------------------
//  Extend Notifications

IJK_EXTERN NSString *const IJKMPMoviePlayerVideoDecoderOpenNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerFirstVideoFrameRenderedNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerFirstAudioFrameRenderedNotification;

IJK_EXTERN NSString *const IJKMPMoviePlayerReceivePTSDTSNotifcation;
IJK_EXTERN NSString *const IJKMPMoviePlayerReceivePTSUserInfoKey;
IJK_EXTERN NSString *const IJKMPMoviePlayerReceiveDTSUserInfoKey;

// Stream Monitor Notifications.
typedef NS_ENUM(int32_t, IJKMPMoviePlayerStreamAbnormalType) {
    IJKMPMoviePlayerStreamAbnormalTypeAdjoin = 0,
    IJKMPMoviePlayerStreamAbnormalTypeVideo = 1,
    IJKMPMoviePlayerStreamAbnormalTypeAudio = 2,
    IJKMPMoviePlayerStreamAbnormalTypeAVStream = 3,
    IJKMPMoviePlayerStreamAbnormalTypeVideoDTSZero = 4
};

IJK_EXTERN NSString *const IJKMPMoviePlayerStreamAbnormalNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerStreamAbnormalTypeInfoKey;
IJK_EXTERN NSString *const IJKMPMoviePlayerPrePTSInfoKey;
IJK_EXTERN NSString *const IJKMPMoviePlayerCurrentPTSInfoKey;

IJK_EXTERN NSString *const IJKMPMoviePlayerNetworkShakeNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerDelayTimeInfoKey;

IJK_EXTERN NSString *const IJKMPMoviePlayerAVFormatTimeNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerOpenTimeInfoKey;
IJK_EXTERN NSString *const IJKMPMoviePlayerFindStreamInfoTimeInfoKey;

IJK_EXTERN NSString *const IJKMPMoviePlayerDecodeErrorNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerFrameQueueNullNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerVideoToolboxFailNotification;

IJK_EXTERN NSString *const IJKMPMoviePlayerNetworkTrafficNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerNetworkTrafficInfoKey;

IJK_EXTERN NSString *const IJKMPMoviePlayerUserDefinedSEINotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerUserDefinedSEIIDInfoKey;
IJK_EXTERN NSString *const IJKMPMoviePlayerUserDefinedSEIPTSInfoKey;
IJK_EXTERN NSString *const IJKMPMoviePlayerUserDefinedSEIMessageInfoKey;

IJK_EXTERN NSString *const IJKMPMoviePlayerAudioPCMNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerAudioPCMData;

IJK_EXTERN NSString *const IJKMPMoviePlayerSwitchResolutionNotification;

IJK_EXTERN NSString *const IJKMPMoviePlayerEnd2EndDelayNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerEnd2EndDelayDetail;

@end

#pragma mark IJKMediaUrlOpenDelegate

typedef NS_ENUM(NSInteger, IJKMediaUrlOpenType) {
    IJKMediaUrlOpenEvent_ConcatResolveSegment = 0x10000,
    IJKMediaUrlOpenEvent_TcpOpen = 0x10001,
    IJKMediaUrlOpenEvent_HttpOpen = 0x10002,
    IJKMediaUrlOpenEvent_LiveOpen = 0x10004,
};

@interface IJKMediaUrlOpenData: NSObject

- (instancetype)initWithUrl:(NSString *)url
         openType:(IJKMediaUrlOpenType)openType
     segmentIndex:(int)segmentIndex
     retryCounter:(int)retryCounter;

@property(nonatomic, readonly) IJKMediaUrlOpenType openType;
@property(nonatomic, readonly) int segmentIndex;
@property(nonatomic, readonly) int retryCounter;

@property(nonatomic, retain) NSString *url;
@property(nonatomic) int error; // set a negative value to indicate an error has occured.
@property(nonatomic, getter=isHandled)    BOOL handled;     // auto set to YES if url changed
@property(nonatomic, getter=isUrlChanged) BOOL urlChanged;  // auto set to YES by url changed

@end

@protocol IJKMediaUrlOpenDelegate <NSObject>

- (void)willOpenUrl:(IJKMediaUrlOpenData*) urlOpenData;

@end
