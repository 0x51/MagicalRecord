//
//  NSAttributeDescription+MagicalDataImport.m
//  Magical Record
//
//  Created by Saul Mora on 9/4/11.
//  Copyright 2011 Magical Panda Software LLC. All rights reserved.
//

#import "NSAttributeDescription+MagicalDataImport.h"
#import "NSManagedObject+MagicalDataImport.h"
#import "MagicalImportFunctions.h"

@implementation NSAttributeDescription (MagicalRecordDataImport)

- (NSString *) MR_primaryKey;
{
    return nil;
}

- (id) MR_valueForKeyPath:(NSString *)keyPath fromObjectData:(id)objectData;
{
    id value = [objectData valueForKeyPath:keyPath];
    
    NSAttributeType attributeType = [self attributeType];
    NSString *desiredAttributeType = [[self userInfo] valueForKey:kMagicalRecordImportAttributeValueClassNameKey];
    if (desiredAttributeType) 
    {
        if ([desiredAttributeType hasSuffix:@"Color"])
        {
            value = MRColorFromString(value);
        }
    }
    else 
    {
        if (attributeType == NSDateAttributeType)
        {
            if (![value isKindOfClass:[NSDate class]]) 
            {
                NSDate *convertedValue = nil;
                NSString *dateFormat;
                NSUInteger index = 0;
                do {
                    NSMutableString *dateFormatKey = [kMagicalRecordImportCustomDateFormatKey mutableCopy];
                    if (index) {
                        [dateFormatKey appendFormat:@".%tu", index];
                    }
                    index++;
                    dateFormat = [[self userInfo] valueForKey:dateFormatKey];

                    if ([value isKindOfClass:[NSNumber class]]) {
                        convertedValue = MRDateFromNumber(value, [dateFormat isEqualToString:kMagicalRecordImportUnixTimeString]);
                    } else {
                        convertedValue = MRDateFromString([value description], dateFormat ?: kMagicalRecordImportDefaultDateFormatString);
                    }

                } while (!convertedValue && dateFormat);
                value = convertedValue;
            }
        }
        else if (attributeType == NSInteger16AttributeType ||
                 attributeType == NSInteger32AttributeType ||
                 attributeType == NSInteger64AttributeType ||
                 attributeType == NSDecimalAttributeType ||
                 attributeType == NSDoubleAttributeType ||
                 attributeType == NSFloatAttributeType) {
            if (![value isKindOfClass:[NSNumber class]] && value != [NSNull null]) {
                value = MRNumberFromString([value description]);
            }
        }
        else if (attributeType == NSBooleanAttributeType) {
            if (![value isKindOfClass:[NSNumber class]] && value != [NSNull null]) {
                value = [NSNumber numberWithBool:[value boolValue]];
            }
        }
        else if (attributeType == NSStringAttributeType) {
            if (![value isKindOfClass:[NSString class]] && value != [NSNull null]) {
                value = [value description];
            }
        }
    }
    
    return value == [NSNull null] ? nil : value;   
}

@end
