//
//  NSManagedObjectContext+MagicalSaves.h
//  Magical Record
//
//  Created by Saul Mora on 3/9/12.
//  Copyright (c) 2012 Magical Panda Software LLC. All rights reserved.
//

#import <CoreData/CoreData.h>

/**
 *  @abstract Options that can be passed when saving a context
 *  @constant MRSaveParentContexts When saving, continue saving parent contexts until the changes are present in the persistent store.
 *  @constant MRSaveSynchronously Peform saves synchronously, blocking execution on the current thread until the save is complete.
 */
typedef NS_OPTIONS(NSUInteger, MRSaveContextOptions) {
    MRSaveParentContexts = 1 << 0,
    MRSaveSynchronously = 1 << 1,
};

typedef void (^MRSaveCompletionHandler)(BOOL success, NSError *error);

@interface NSManagedObjectContext (MagicalSaves)

/**
 *  Asynchronously save changes in the current context and it's parent.
 *  Executes a save on the current context's dispatch queue asynchronously. This method only saves the current context, and the parent of the current context if one is set.
 *
 *  @param completion Completion block that is called after the save has completed. The block is passed a success state as a `BOOL` and an `NSError` instance if an error occurs.
 */
- (void) MR_saveOnlySelfWithCompletion:(MRSaveCompletionHandler)completion;

/**
 *  Asynchronously save changes in the current context all the way back to the persistent store.
 *  Executes asynchronous saves on the current context, and any ancestors, until the changes have been persisted to the assigned persistent store.
 *
 *  @param completion Completion block that is called after the save has completed. The block is passed a success state as a `BOOL` and an `NSError` instance if an error occurs.
 */
- (void) MR_saveToPersistentStoreWithCompletion:(MRSaveCompletionHandler)completion;

/**
 *  Synchronously save changes in the current context and it's parent.
 *  Executes a save on the current context's dispatch queue. This method only saves the current context, and the parent of the current context if one is set. The method will not return until the save is complete.
 *
 *  @return Success state of the save
 */
- (BOOL) MR_saveOnlySelfAndWait;

/**
 *  Synchronously save changes in the current context and merge changes to it's parent.
 *
 *  @param error Pass in an NSError by reference to receive any errors encountered during the save.
 *
 *  @return Success state of the save
 */
- (BOOL) MR_saveOnlySelfAndWaitWithError:(NSError **)error;

/**
 *  Synchronously save changes in the current context all the way back to the persistent store. 
 *  Executes saves on the current context, and any ancestors, until the changes have been persisted to the assigned persistent store. The method will not return until the save is complete.
 *
 *  @return Success state of the save
 */
- (BOOL) MR_saveToPersistentStoreAndWait;

/**
 *  Synchronously save changes in the current context all the way back to the persistent store.
 *
 *  @param error Pass in an NSError by reference to receive any errors encountered during the save.
 *
 *  @return Success state of the save
 */
- (BOOL) MR_saveToPersistentStoreAndWaitWithError:(NSError **)error;

/**
 *  Save the current context with options. All other save methods are convenience wrappers around this method.
 *
 *  @param mask       bitmasked options for the save process
 *  @param completion Completion block that is called after the save has completed. The block is passed a success state as a `BOOL` and an `NSError` instance if an error occurs
 */
 - (void) MR_saveWithOptions:(MRSaveContextOptions)mask completion:(MRSaveCompletionHandler)completion;

@end
