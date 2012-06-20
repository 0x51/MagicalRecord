//
//  FixtureHelpers.h
//  Magical Record
//
//  Created by Saul Mora on 7/15/11.
//  Copyright 2011 Magical Panda Software LLC. All rights reserved.
//
#import <SenTestingKit/SenTestingKit.h>
@interface FixtureHelpers : NSObject

+ (id) dataFromPListFixtureNamed:(NSString *)fixtureName;
+ (id) dataFromJSONFixtureNamed:(NSString *)fixtureName;

@end


@interface SenTestCase (FixtureHelpers)

- (id) dataFromJSONFixture;

@end

@interface Address : NSObject
@end


@interface User : NSObject
@property (nonatomic, strong) Address *userAddress;
@property (nonatomic, copy) NSString *firstName;
@property (nonatomic, copy) NSString *lastName;
@end
