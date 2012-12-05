//
//  IAUserSearchBar.h
//  FinderWindowApplication
//
//  Created by infinit on 11/5/12.
//  Copyright (c) 2012 infinit. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface IAUserSearchBar : NSSearchField

- (NSString*)getUser;
- (BOOL)isValid;


@end
