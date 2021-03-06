//
//  SCVideoPlayer.h
//  SCAudioVideoRecorder
//
//  Created by Simon CORSIN on 8/30/13.
//  Copyright (c) 2013 rFlex. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

@class SCPlayer;

@protocol SCVideoPlayerDelegate <NSObject>

@optional

- (void) videoPlayer:(SCPlayer*)videoPlayer didPlay:(Float64)secondsElapsed loopsCount:(NSInteger)loopsCount;
- (void) videoPlayer:(SCPlayer *)videoPlayer didStartLoadingAtItemTime:(CMTime)itemTime;
- (void) videoPlayer:(SCPlayer *)videoPlayer didEndLoadingAtItemTime:(CMTime)itemTime;
- (void) videoPlayer:(SCPlayer *)videoPlayer didChangeItem:(AVPlayerItem*)item;

@end

@interface SCPlayer : AVPlayer

+ (SCPlayer*) player;
+ (void) pauseCurrentPlayer;
+ (SCPlayer*) currentPlayer;

// Ask the SCPlayer to send didPlay messages during the playback
// endSendingPlayMessages must be called, otherwise the SCPlayer will never
// be deallocated
- (void)beginSendingPlayMessages;
// Ask the SCPlayer to stop sending didPlay messages during the playback
- (void)endSendingPlayMessages;

- (void) setItemByStringPath:(NSString*)stringPath;
- (void) setItemByUrl:(NSURL*)url;
- (void) setItemByAsset:(AVAsset*)asset;
- (void) setItem:(AVPlayerItem*)item;

// These methods allow the player to add the same item "loopCount" time
// in order to have a smooth loop. The loop system provided by Apple
// has an unvoidable hiccup. Using these methods will avoid the hiccup for "loopCount" time

- (void) setSmoothLoopItemByStringPath:(NSString*)stringPath smoothLoopCount:(NSUInteger)loopCount;
- (void) setSmoothLoopItemByUrl:(NSURL*)url smoothLoopCount:(NSUInteger)loopCount;
- (void) setSmoothLoopItemByAsset:(AVAsset*)asset smoothLoopCount:(NSUInteger)loopCount;

- (CMTime) itemDuration;
- (CMTime) playableDuration;
- (BOOL) isPlaying;
- (BOOL) isLoading;

@property (weak, nonatomic, readwrite) id<SCVideoPlayerDelegate> delegate;
@property (assign, nonatomic, readwrite) CMTime minimumBufferedTimeBeforePlaying;
@property (assign, nonatomic, readwrite) BOOL shouldLoop;
@property (nonatomic, readonly) BOOL isSendingPlayMessages;

@end
